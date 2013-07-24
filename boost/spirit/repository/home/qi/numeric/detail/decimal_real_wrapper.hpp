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
	typedef std::vector<std::uint32_t> num_type;

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

	constexpr static std::uint32_t dec_num_radix = 1000000;

	num_type mantissa;
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

			out.back_scale /= 10;
			out.mantissa.back()
			+= out.back_scale * ascii_digit_value<10>(in);

			if (out.back_scale == 1UL) {
				out.mantissa.push_back(0);
				out.back_scale = dec_num_radix;
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
	: mantissa(1, 0),
	  back_scale(dec_num_radix),
	  int_scale(0), exponent(0)
	{}

	operator T() const;

private:
	static std::array<
		std::tuple<
			int,
			std::uint32_t,
			std::uint32_t
		>, 13
	> const tab_pow_2_1;

	static std::array<
		std::tuple<
			int,
			std::uint32_t,
			std::uint32_t
		>, 13
	> const tab_pow_2;

	static std::array<
		std::tuple<
			int,
			std::uint32_t,
			std::uint32_t,
			std::uint32_t,
			std::uint32_t,
			std::uint32_t
		>, 13
	> const tab_pow_5;

	static void scale(num_type &m, int &d_exp, int &b_exp);

	static void normalize(num_type &m, int &d_exp, int &b_exp);

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
	if (mantissa.empty()) {
		return std::copysign(T(0), sign ? T(-1) : T(1));
	};

	num_type m(mantissa);

	//int adj_scale(mantissa.cend() - pos_e);
	int d_exp(int_scale);

	adj_scale = pos_b - mantissa.cbegin();
	d_exp -= adj_scale;

	d_exp += exponent;

	int b_exp(0);

	while (d_exp > 0)
		scale(m, d_exp, b_exp);

	while (d_exp < 0 || m[0] < (dec_num_radix / 2))
		normalize(m, d_exp, b_exp);

	adj_scale = std::min(
		static_cast<int>(m.size()), std::numeric_limits<T>::digits10
	);

	T val(std::accumulate(
		m.cbegin(), m.cbegin() + adj_scale, T(0),
		[](T v, num_type::value_type d) -> T {
			return v * dec_num_radix + d;
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

	int b(std::get<0>(tab_pow_2_1[d]));

	if (std::get<1>(tab_pow_2_1[d]) < m[0]) {
		--d;
	} else if (std::get<1>(tab_pow_2_1x[d]) == m[0]) {
		if (m.size() > 1 && std::get<2>(tab_pow_2_1[d]) < m[1])
			--d;
	}

	d_exp -= d;
	b_exp += b;

	constexpr static long long dec_num_radix_sqr
	= static_cast<long long>(dec_num_radix) * dec_num_radix;

	num_type1 q(1, 0);
	num_type1 u(m.size() + 3UL, 0);
	std::copy(m.cbegin(), m.cend(), u.begin() + 1);

	num_type1::value_type v[2] = {
		std::get<1>(tab_pow_2[d]),
		std::get<2>(tab_pow_2[d])
	};

	long long lv(static_cast<long long>(v[0]) * dec_num_radix + v[1]);
	long long acc[3], qx;
	bool borrow(false);

repeat:
	u[0] = 0;
	for (auto uj(u.begin()); uj != (u.end() - 2); ++uj) {
		acc[0] = *uj;
		acc[0] *= dec_num_radix;
		acc[0] += *(uj + 1);

		if (*uj == v[0])
			qx = dec_num_radix - 1;
		else {
			qx = acc[0] / v[0];
			while ((qx * v[1]) > (
				(acc[0] - qx * v[0])
				* dec_num_radix + *(uj + 2)
			))
				--qx;
		}

		acc[0] *= dec_num_radix;
		acc[0] += *(uj + 2);
		acc[1] = qx * lv;
		if (acc[0] >= acc[1]) {
			borrow = false;
			acc[1] = acc[0] - acc[1];
		} else {
			borrow = true;
			acc[1] = dec_num_radix_sqr - acc[1] + acc[0];
		}

		*uj = acc[1] / dec_num_radix_sqr;
		acc[1] %= dec_num_radix_sqr;
		*(uj + 1) = acc[1] / dec_num_radix;
		*(uj + 2) = acc[1] % dec_num_radix;

		if (!q.back()) {
			if (qx)
				q.back() = qx;
		} else
			q.push_back(qx);

		if (borrow) {
			--q.back();
			acc[0] = *(uj + 1);
			acc[0] *= dec_num_radix;
			acc[0] += *(uj + 2);
			acc[0] += lv;
			*uj = ((acc[0] / dec_num_radix_sqr) + *uj)
			      % dec_num_radix;
			acc[1] = acc[0] % dec_num_radix_sqr;
			*(uj + 1) = acc[1] / dec_num_radix;
			*(uj + 2) = acc[1] % dec_num_radix;
		}
	};

	u.erase(u.begin() + 1, u.end() - 2);
	if (std::any_of(u.cbegin(), u.cend(), [](num_type1::value_type uj) {
		return uj != 0;
	})) {
		u.push_back(0);
		goto repeat;
	}

	m.swap(q);
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
	std::tuple<
		int,
		typename decimal_real_wrapper<T>::num_type::value_type,
		typename decimal_real_wrapper<T>::num_type::value_type
	>, 13
> const decimal_real_wrapper<T>::tab_pow_2_1 = {{
	std::make_tuple(1,  0, 0),
	std::make_tuple(3,  700000, 0),
	std::make_tuple(6,  630000, 0),
	std::make_tuple(9,  511000, 0),
	std::make_tuple(13, 819100, 0),
	std::make_tuple(16, 655350, 0),
	std::make_tuple(19, 524287, 0),
	std::make_tuple(23, 838860, 700000),
	std::make_tuple(26, 671088, 630000),
	std::make_tuple(29, 536870, 911000),
	std::make_tuple(33, 858993, 459100),
	std::make_tuple(36, 687194, 767350),
	std::make_tuple(39, 549755, 813887)
}};

template <typename T>
std::array<
	std::tuple<
		int,
		typename decimal_real_wrapper<T>::num_type::value_type,
		typename decimal_real_wrapper<T>::num_type::value_type
	>, 13
> const decimal_real_wrapper<T>::tab_pow_2 = {{
	std::make_tuple(1,  0, 0),
	std::make_tuple(3,  800000, 0),
	std::make_tuple(6,  640000, 0),
	std::make_tuple(9,  512000, 0),
	std::make_tuple(13, 819200, 0),
	std::make_tuple(16, 655360, 0),
	std::make_tuple(19, 524288, 0),
	std::make_tuple(23, 838860, 800000),
	std::make_tuple(26, 671088, 640000),
	std::make_tuple(29, 536870, 912000),
	std::make_tuple(33, 858993, 459200),
	std::make_tuple(36, 687194, 767360),
	std::make_tuple(39, 549755, 813888)
}};

template <typename T>
std::array<
	std::tuple<
		int,
		typename decimal_real_wrapper<T>::num_type::value_type,
		typename decimal_real_wrapper<T>::num_type::value_type,
		typename decimal_real_wrapper<T>::num_type::value_type,
		typename decimal_real_wrapper<T>::num_type::value_type,
		typename decimal_real_wrapper<T>::num_type::value_type
	>, 13
> const decimal_real_wrapper<T>::tab_pow_5 = {{
	std::make_tuple(1,  0,      0,      0,      0,      0),
	std::make_tuple(3,  125000, 0,      0,      0,      0),
	std::make_tuple(6,  156250, 0,      0,      0,      0),
	std::make_tuple(9,  195312, 500000, 0,      0,      0),
	std::make_tuple(13, 122070, 312500, 0,      0,      0),
	std::make_tuple(16, 152587, 890625, 0,      0,      0),
	std::make_tuple(19, 190734, 863281, 250000, 0,      0),
	std::make_tuple(23, 119209, 289550, 781250, 0,      0),
	std::make_tuple(26, 149011, 611938, 476562, 500000, 0),
	std::make_tuple(29, 186264, 514923, 095703, 125000, 0),
	std::make_tuple(33, 116415, 321826, 934814, 453125, 0),
	std::make_tuple(36, 145519, 152283, 668518,  66406, 250000),
	std::make_tuple(39, 181898, 940354, 585647, 583007, 812500)
}};

}
}}}}

#endif
