/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Based on the implementation by:

        Rob Pike and Ken Thompson
        Copyright (c) 2002 by Lucent Technologies.

            Permission to use, copy, modify, and distribute this software for
            any purpose without fee is hereby granted, provided that this
            entire notice is included in all copies of any software which is or
            includes a copy or modification of this software and in all copies
            of the supporting documentation for such software.

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815)
#define SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815

#include <boost/spirit/repository/home/qi/numeric/numeric_utils.hpp>

#include <cmath>
#include <array>
#include <initializer_list>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename T>
struct decimal_real_wrapper {
	typedef decimal_real_wrapper<T> wrapper_type;
	typedef std::vector<uint8_t> num_type;
	constexpr static T const initial_error_bound = 1e-8;

	num_type mantissa;
	bool sign;
	int int_scale;
	int exponent;

	template <bool Negative = false>
	struct integer_op {
		typedef integer_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			out.sign = Negative;
			out.mantissa.push_back(ascii_digit_value<10>(in));
			++out.int_scale;
			return true;
		}
	};

	template <bool Negative = false>
	struct fraction_op {
		typedef fraction_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			out.sign = Negative;
			out.mantissa.push_back(ascii_digit_value<10>(in));
			return true;
		}
	};

	template <bool Negative = false>
	struct exponent_op {
		typedef exponent_op<!Negative> opposite_type;

		template <typename CharType, bool Negative_ = false>
		struct impl {
			bool operator()(CharType in, wrapper_type &out)
			{
				out.exponent *= 10;
				out.exponent += ascii_digit_value<10>(in);
				return true;
			}
		};

		template <typename CharType>
		struct impl<CharType, true> {
			bool operator()(CharType in, wrapper_type &out)
			{
				out.exponent *= 10;
				out.exponent -= ascii_digit_value<10>(in);
				return true;
			}
		};

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			return impl<CharType, Negative>()(in, out);
		}
	};

	decimal_real_wrapper()
	: int_scale(0), exponent(0)
	{}

	operator T() const;

private:
	static std::array<
		std::pair<int, num_type>, 10
	> const tab_pow_2_1;

	static std::array<
		std::pair<int, num_type>, 10
	> const tab_pow_5;

	static void scale(num_type &m, int &d_exp, int &b_exp);
	static void normalize(num_type &m, int &d_exp, int &b_exp);
	static long target_cmp(num_type &m, T val);
};

template <typename T>
decimal_real_wrapper<T>::operator T() const
{
	auto pos_b(mantissa.cbegin()), pos_e(mantissa.cend());

	while (!*pos_b)
		++pos_b;

	while (pos_e != mantissa.cbegin()) {
		--pos_e;
		if (*pos_e) {
			++pos_e;
			break;
		}
	}

	num_type m(pos_b, pos_e);
	int adj_scale(pos_e - mantissa.cend());
	int d_exp(int_scale);

	if (adj_scale > static_cast<int>(mantissa.size() - int_scale))
		d_exp += adj_scale - (mantissa.size() - int_scale);

	adj_scale = mantissa.cbegin() - pos_b;
	if (adj_scale > int_scale)
		d_exp -=adj_scale - int_scale;

	d_exp += exponent;

	int b_exp(0);

	while (d_exp > 0)
		scale(m, d_exp, b_exp);

	while (d_exp < 0 || m[0] < 5)
		normalize(m, d_exp, b_exp);

	adj_scale = std::min(
		static_cast<int>(m.size()), std::numeric_limits<T>::digits10
	);
	T val(std::accumulate(
		m.cbegin(), m.cbegin() + adj_scale, T(0),
		[](T v, num_type::value_type d) -> T {
			return v * 10 + d;
		}
	));
	T high, low, last(initial_error_bound);

	val *= std::pow(10, -adj_scale);;

	val = std::frexp(val, &adj_scale);

	int c(target_cmp(m, val));
	int x(0);

	if (c > 0) {
		low = val;
		high = val + last;
	} else if (c < 0) {
		high = val;
		low = val - last;
	} else
		goto out;

	do {
		last = val;
		val = (high + low) / 2;
		val = std::frexp(val, &adj_scale);

		c = target_cmp(m, val);

		if (c > 0)
			low = val;

		if (c < 0)
			high = val;

		
		++x;
	} while(c && val != last);
	std::cout << "iter: " << x << '\n';
out:
	return std::copysign(
		std::ldexp(val, b_exp),
		sign ? T(-1) : T(1)
	);
}

template <typename T>
void decimal_real_wrapper<T>::scale(num_type &m, int &d_exp, int &b_exp)
{
	int d(d_exp);

	if (d >= static_cast<int>(tab_pow_2_1.size()))
		d = tab_pow_2_1.size() - 1;

	int b(tab_pow_2_1[d].first);
	if (std::lexicographical_compare(
		m.cbegin(), m.cend(),
		tab_pow_2_1[d].second.cbegin(), tab_pow_2_1[d].second.cend(),
		std::greater<num_type::value_type>()
	))
		--d;

	d_exp -= d;
	b_exp += b;

	int n(0), c(0);
	auto p(m.begin()), q(m.begin());

	while (!(n >> b)) {
		c = *p++;
		n = n * 10 + c;
		if (p == m.end()) {
			
			while (n) {
				c = n * 10;
				if (c >> b)
					break;

				n = c;
			}
			goto out;
		}
	};

	while (true) {
		c = n >> b;
		n -= c << b;
		*q++ = c;
		if (p == m.end())
			break;
		c = *p++;
		n = n * 10 + c;
	}
out:
	while (n && q != m.end()) {
		n = n * 10;
		c = n >> b;
		n -= c << b;
		*q++ = c;
	};
	while (n) {
		n = n * 10;
		c = n >> b;
		n -= c << b;
		m.push_back(c);
	};
}

template <typename T>
void decimal_real_wrapper<T>::normalize(num_type &m, int &d_exp, int &b_exp)
{
	int d(-d_exp);
	if (d >= static_cast<int>(tab_pow_5.size()))
		d = tab_pow_5.size() - 1;

	int b(tab_pow_5[d].first);
	if (std::lexicographical_compare(
		m.cbegin(), m.cend(),
		tab_pow_5[d].second.cbegin(), tab_pow_5[d].second.cend(),
		std::less<num_type::value_type>()
	))
		--d;

	b_exp -= b;
	d_exp += d;

	int n(0), c(0);
	m.insert(m.end(), d, uint8_t(0));
	auto p(m.end());
	auto q(m.end() - d);

	do {
		--q;
		c = *q;
		c = (c << b) + n;
		n = c / 10;
		c -= n * 10;
		--p;
		*p = c;
	} while (q != m.begin());

	while (n) {
		c = n;
		n = c / 10;
		c -= n * 10;
		--p;
		*p = c;
	}
}

template <typename T>
long decimal_real_wrapper<T>::target_cmp(num_type &m, T val)
{
	T next_val;
	long rv;

	for (auto v : m) {
		next_val = std::modf(val * 10, &val);
		rv = static_cast<long>(v) - std::lrint(val);
		if (rv)
			return rv;

		val = next_val;
	}

	while (true) {
		next_val = std::modf(val * 10, &val);
		rv = 0 - std::lrint(val);
		if (rv)
			return rv;
		else if (next_val == 0)
			return 0;

		val = next_val;
	}
}

template <typename T>
std::array<
	std::pair<int, std::vector<uint8_t>>, 10
> const decimal_real_wrapper<T>::tab_pow_2_1 = {{
	std::make_pair(1, num_type()),
	std::make_pair(3, num_type({7})),
	std::make_pair(6, num_type({6, 3})),
	std::make_pair(9, num_type({5, 1, 1})),
	std::make_pair(13, num_type({8, 1, 9, 1})),
	std::make_pair(16, num_type({6, 5, 5, 3, 5})),
	std::make_pair(19, num_type({5, 2, 4, 2, 8, 7})),
	std::make_pair(23, num_type({8, 3, 8, 8, 6, 0, 7})),
	std::make_pair(26, num_type({6, 7, 1, 0, 8, 8, 6, 3})),
	std::make_pair(27, num_type({1, 3, 4, 2, 1, 7, 7, 2, 7}))
}};

template <typename T>
std::array<
	std::pair<int, std::vector<uint8_t>>, 10
> const decimal_real_wrapper<T>::tab_pow_5 = {{
	std::make_pair(1, num_type()),
	std::make_pair(3, num_type({
		1, 2, 5
	})),
	std::make_pair(6, num_type({
		1, 5, 6, 2, 5
	})),
	std::make_pair(9, num_type({
		1, 9, 5, 3, 1, 2, 5
	})),
	std::make_pair(13, num_type({
		1, 2, 2, 0, 7, 0, 3, 1, 2, 5
	})),
	std::make_pair(16, num_type({
		1, 5, 2, 5, 8, 7, 8, 9, 0, 6, 2, 5
	})),
	std::make_pair(19, num_type({
		1, 9, 0, 7, 3, 4, 8, 6, 3, 2, 8, 1, 2, 5
	})),
	std::make_pair(23, num_type({
		1, 1, 9, 2, 0, 9, 2, 8, 9, 5, 5, 0, 7, 8, 1, 2, 5
	})),
	std::make_pair(26, num_type({
		1, 4, 9, 0, 1, 1, 6, 1, 1, 9, 3, 8, 4, 7, 6, 5, 6, 2, 5
	})),
	std::make_pair(27, num_type({
		7, 4, 5, 0, 5, 8, 0, 5, 9, 6, 9, 2, 3, 8, 2, 8, 1, 2, 5
	}))
}};

}
}}}}

#endif


