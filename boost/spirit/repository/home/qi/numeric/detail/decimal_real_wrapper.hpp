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

#include <boost/spirit/repository/home/support/radix_pow.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_utils.hpp>

#include <cmath>
#include <array>
#include <tuple>
#include <initializer_list>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename T>
struct decimal_real_wrapper {
	typedef decimal_real_wrapper<T> wrapper_type;
	typedef std::vector<uint8_t> num_type;
	typedef std::vector<std::uint32_t> num_type1;

	constexpr static int mantissa_bits = std::numeric_limits<T>::digits;

	/* 4 bits "guard space" is necessary to avoid overflow from
	 * multiplication by 10.
	 */
	constexpr static int word_bits
	= std::numeric_limits<unsigned long>::digits - 4;

	constexpr static int bigint_words
	= (mantissa_bits + word_bits + 1) / word_bits;

	typedef std::array<unsigned long, bigint_words> bigint_type;

	/* Normalized mantissa value obtained by naive conversion is expected
	 * to contain at least that many correct bits. This should be
	 * calculatable somehow.
	 */
	static int const initial_true_bits;

	/* Least significant value bit in the bigint expansion. */
	constexpr static unsigned long sig_bit_mask
	= 1UL << (bigint_words * word_bits - mantissa_bits);

	constexpr static std::uint32_t max_dec_leaf_value = 100000000;

	num_type mantissa;
	num_type1 mantissa1;
	bool sign;
	unsigned long back_scale;
	int int_scale;
	int exponent;

	template <bool Negative = false>
	struct fraction_op {
		typedef fraction_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			out.sign = Negative;

			out.mantissa.push_back(ascii_digit_value<10>(in));

			out.back_scale /= 10;
			out.mantissa1.back()
			+= out.back_scale * ascii_digit_value<10>(in);

			if (out.back_scale == 1UL) {
				out.mantissa1.push_back(0);
				out.back_scale = max_dec_leaf_value;
			}

			return true;
		}
	};

	template <bool Negative = false>
	struct integer_op {
		typedef integer_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			auto d(ascii_digit_value<10>(in));
			if (!out.int_scale && !d)
				return true;

			auto rv(fraction_op<Negative>()(in, out));
			if (rv)
				++out.int_scale;
			return rv;
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
	: mantissa1(1, 0),
	  back_scale(max_dec_leaf_value),
	  int_scale(0), exponent(0)
	{}

	operator T() const;

private:
	static std::array<
		std::pair<int, num_type>, 10
	> const tab_pow_2_1;

	static std::array<
		std::tuple<
			int,
			std::uint32_t,
			std::uint32_t
		>, 17
	> const tab_pow_2_1x;

	static std::array<
		std::pair<int, num_type>, 10
	> const tab_pow_5;

	static void scale(num_type &m, int &d_exp, int &b_exp);
	static void scale(num_type1 &m, int &d_exp, int &b_exp);

	static void normalize(num_type &m, int &d_exp, int &b_exp);
	static void normalize(num_type1 &m, int &d_exp, int &b_exp);

	static void real_to_bigint(T val, bigint_type &low, bigint_type &high);
	static void bigint_average(
		bigint_type const &low, bigint_type const &high,
		bigint_type &mid
	);
	static bool bigint_assign_cmp(bigint_type const &src, bigint_type &dst);
	static void bigint_normalize(bigint_type &val);
	static int target_cmp(num_type const &m, bigint_type const &val);
};

template <typename T>
constexpr int decimal_real_wrapper<T>::word_bits;

template <>
int const decimal_real_wrapper<float>::initial_true_bits = 16;

template <>
int const decimal_real_wrapper<double>::initial_true_bits = 32;

template <>
int const decimal_real_wrapper<long double>::initial_true_bits = 48;

template <typename T>
decimal_real_wrapper<T>::operator T() const
{
	auto pos_b(mantissa.cbegin()), pos_e(mantissa.cend());

	for (; pos_b != pos_e; ++pos_b)
		if (*pos_b)
			break;

	while (pos_e != pos_b) {
		--pos_e;
		if (*pos_e) {
			++pos_e;
			break;
		}
	}

	num_type m(pos_b, pos_e);
	if (m.empty()) {
		return std::copysign(T(0), sign ? T(-1) : T(1));
	};

	num_type1 m1(mantissa1);
	int adj_scale(mantissa.cend() - pos_e);
	int d_exp(int_scale);

	adj_scale = pos_b - mantissa.cbegin();
	d_exp -= adj_scale;

	d_exp += exponent;

	int b_exp(0);
	int d_exp1(d_exp), b_exp1(b_exp);

	while (d_exp > 0) {
		scale(m, d_exp, b_exp);
		scale(m1, d_exp1, b_exp1);
	}

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

	val *= std::pow(T(10), -adj_scale);

	bigint_type low, mid, high;
	real_to_bigint(val, low, high);

	int x(0);

	while (true) {
		bigint_average(low, high, mid);
		auto c(target_cmp(m, mid));

		if (c > 0) {
			if (bigint_assign_cmp(mid, low))
				break;
		} else if (c < 0)
			bigint_assign_cmp(mid, high);
		else {
			auto tail(mid.back() & (sig_bit_mask - 1UL));
			if (
				tail == (sig_bit_mask >> 1)
				&& !(mid.back() & sig_bit_mask)
			)
				mid.back() -= tail;

			break;
		}

		++x;
	};
	auto tail(mid.back() & (sig_bit_mask - 1UL));
	mid.back() -= tail;
	if (tail >= (sig_bit_mask >> 1)) {
		mid.back() += sig_bit_mask;
		bigint_normalize(mid);
	}

	val = 0;
	for (auto v : mid) {
		val = std::ldexp(val, word_bits);
		val += v;
	}

	return std::copysign(
		std::ldexp(val, b_exp - word_bits * mid.size()),
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
		tab_pow_2_1[d].second.cbegin(), tab_pow_2_1[d].second.cend(),
		m.cbegin(), m.cend()
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
			if (n >> b)
				break;
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
void decimal_real_wrapper<T>::scale(num_type1 &m, int &d_exp, int &b_exp)
{
	int d(d_exp);

	if (d >= static_cast<int>(tab_pow_2_1x.size()))
		d = tab_pow_2_1x.size() - 1;

	int b(std::get<0>(tab_pow_2_1x[d]));

	if (std::get<1>(tab_pow_2_1x[d]) < m[0]) {
		--d;
	} else if (std::get<1>(tab_pow_2_1x[d]) == m[0]) {
		if (m.size() > 1 && std::get<2>(tab_pow_2_1x[d]) < m[1])
			--d;
	}

	d_exp -= d;
	b_exp += b;

	long long n(0), c(0);
	auto p(m.begin()), q(m.begin());

	while (!(n >> b)) {
		c = *p++;
		n = n * max_dec_leaf_value + c;
		if (p == m.end()) {
			if (n >> b)
				break;
			while (n) {
				c = n * max_dec_leaf_value;
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
		n = n * max_dec_leaf_value + c;
	}
out:
	while (n && q != m.end()) {
		n = n * max_dec_leaf_value;
		c = n >> b;
		n -= c << b;
		*q++ = c;
	};
	while (n) {
		n = n * max_dec_leaf_value;
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
void decimal_real_wrapper<T>::real_to_bigint(
	T val, bigint_type &low, bigint_type &high
)
{
	int exp, adj_exp(0);
	T int_val;
	typename bigint_type::size_type pos(0);

	do {
		val = std::frexp(val, &exp);
		exp = std::min(word_bits, initial_true_bits - adj_exp);
		val = std::ldexp(val, exp);
		val = std::modf(val, &int_val);
		low[pos] = std::lrint(int_val);
		low[pos] <<= word_bits - exp;
		high[pos] = low[pos] | ((1UL << (word_bits - exp)) - 1UL);
		adj_exp += exp;
		++pos;
	} while ((adj_exp < initial_true_bits) && (pos < low.size()));

	while (pos < low.size()) {
		low[pos] = 0;
		high[pos++] = (1UL << word_bits) - 1UL;
	}
}

template <typename T>
void decimal_real_wrapper<T>::bigint_average(
	bigint_type const &low, bigint_type const &high,
	bigint_type &mid
)
{
	typename bigint_type::size_type bigint_pos(0);
	long c(0);

	for (; bigint_pos < mid.size(); ++bigint_pos) {
		mid[bigint_pos] = high[bigint_pos] + low[bigint_pos];
		if (c)
			mid[bigint_pos] += 1UL << word_bits;

		c = mid[bigint_pos] & 1UL;
		mid[bigint_pos] >>= 1;
	}

	c = 0;
	for (--bigint_pos; bigint_pos; --bigint_pos) {
		mid[bigint_pos] += c;
		c = mid[bigint_pos] >> word_bits;
		mid[bigint_pos] &= (1UL << word_bits) - 1UL;
	}
	mid[0] += c;
}

template <typename T>
bool decimal_real_wrapper<T>::bigint_assign_cmp(
	bigint_type const &src, bigint_type &dst
)
{
	typename bigint_type::size_type dst_pos(0);
	bool eq(true);

	for (auto v : src) {
		eq = eq && (dst[dst_pos] == v);
		dst[dst_pos++] = v;
	}

	return eq;
}

template <typename T>
void decimal_real_wrapper<T>::bigint_normalize(bigint_type &val)
{
	typename bigint_type::value_type c(0);

	for (auto pos(val.size() - 1); pos > 0; --pos) {
		val[pos] += c;
		c = val[pos] >> word_bits;
		val[pos] &= (1UL << word_bits) - 1UL;
	}

	val[0] += c;
}

template <typename T>
int decimal_real_wrapper<T>::target_cmp(
	num_type const &m, bigint_type const &val
)
{
	bigint_type m_val(val);
	std::function<int (bigint_type &)> next_digit(
		[](bigint_type &val) -> int {
			std::for_each(
				val.begin(), val.end(),
				[](typename bigint_type::value_type &v) {
					v *= 10;
				}
			);
			bigint_normalize(val);
			int d(val[0] >> word_bits);
			val[0] &= (1UL << word_bits) - 1UL;
			return d;
		}
	);

	for (int c : m) {
		auto d(next_digit(m_val));
		if (c - d)
			return c - d;
	}

	while (true) {
		auto d(next_digit(m_val));
		if (0 - d)
			return 0 - d;
		if (std::all_of(
			m_val.begin(), m_val.end(),
			[](typename bigint_type::value_type v) -> bool {
				return v == 0;
			}
		))
			return 0;
	}
}

template <typename T>
std::array<
	std::pair<int, std::vector<uint8_t>>, 10
> const decimal_real_wrapper<T>::tab_pow_2_1 = {{
	std::make_pair(1,  num_type()),
	std::make_pair(3,  num_type({7})),
	std::make_pair(6,  num_type({6, 3})),
	std::make_pair(9,  num_type({5, 1, 1})),
	std::make_pair(13, num_type({8, 1, 9, 1})),
	std::make_pair(16, num_type({6, 5, 5, 3, 5})),
	std::make_pair(19, num_type({5, 2, 4, 2, 8, 7})),
	std::make_pair(23, num_type({8, 3, 8, 8, 6, 0, 7})),
	std::make_pair(26, num_type({6, 7, 1, 0, 8, 8, 6, 3})),
	std::make_pair(27, num_type({1, 3, 4, 2, 1, 7, 7, 2, 7}))
}};

template <typename T>
std::array<
	std::tuple<
		int,
		typename decimal_real_wrapper<T>::num_type1::value_type,
		typename decimal_real_wrapper<T>::num_type1::value_type
	>, 17
> const decimal_real_wrapper<T>::tab_pow_2_1x = {{
	std::make_tuple(1,  0, 0),
	std::make_tuple(3,  70000000, 0),
	std::make_tuple(6,  63000000, 0),
	std::make_tuple(9,  51100000, 0),
	std::make_tuple(13, 81910000, 0),
	std::make_tuple(16, 65535000, 0),
	std::make_tuple(19, 52428700, 0),
	std::make_tuple(23, 83886070, 0),
	std::make_tuple(26, 67108863, 0),
	std::make_tuple(29, 53687091, 10000000),
	std::make_tuple(33, 85899345, 92000000),
	std::make_tuple(36, 68719476, 73600000),
	std::make_tuple(39, 54975581, 38880000),
	std::make_tuple(43, 87960930, 22208000),
	std::make_tuple(46, 70368744, 17766400),
	std::make_tuple(49, 56294995, 34213120),
	std::make_tuple(53, 90071992, 54740992)
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


