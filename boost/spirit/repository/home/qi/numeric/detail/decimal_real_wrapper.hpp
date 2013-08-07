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

#include <boost/spirit/repository/home/support/bignum_utils.hpp>
#include <boost/spirit/repository/home/support/static_table.hpp>
#include <boost/spirit/repository/home/support/detail/pow_2.hpp>
#include <boost/spirit/repository/home/support/detail/pow_2m1.hpp>
#include <boost/spirit/repository/home/support/detail/rec_pow_2.hpp>
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
	typedef std::vector<unsigned long> src_num_type;

	constexpr static int mantissa_bits = std::numeric_limits<T>::digits;

	/* Leave some room for carry. */
	constexpr static int word_bits
	= std::numeric_limits<unsigned long>::digits - 2;

	constexpr static int bigint_words
	= (mantissa_bits + word_bits + 1) / word_bits;

	typedef std::array<unsigned long, bigint_words> dst_num_type;

	/* Normalized mantissa value obtained by naive conversion is expected
	 * to contain at least that many correct bits. This should be
	 * calculatable somehow.
	 */
	static int const initial_true_bits;

	/* Least significant value bit in the bigint expansion. */
	constexpr static unsigned long sig_bit_mask
	= 1UL << (bigint_words * word_bits - mantissa_bits);

#ifdef __LP64__
	constexpr static long src_num_radix = 1000000000000000000L;
#else
	constexpr static long src_num_radix = 1000000000L;
#endif

	src_num_type mantissa;
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
				out.back_scale = src_num_radix;
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
	  back_scale(src_num_radix),
	  int_scale(0), exponent(0)
	{}

	operator T() const;

private:
	static void scale_down(src_num_type &m, int &d_exp, int &b_exp);
	static void scale_up(src_num_type &m, int &d_exp, int &b_exp);

	static void real_to_dst_num_type(
		dst_num_type &high, dst_num_type &low, T val
	);
	static void dst_num_type_average(
		dst_num_type &mid, dst_num_type const &high,
		dst_num_type const &low
	);
	static bool dst_num_type_assign_cmp(
		dst_num_type &dst, dst_num_type const &src
	);
	static void dst_num_type_normalize(dst_num_type &val);
	static int target_cmp(dst_num_type const &val, src_num_type const &m);
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

	src_num_type m;
	{
		auto iter(mantissa.cend());
		while (iter > mantissa.cbegin() && !(*(iter - 1)))
			--iter;
		m.assign(mantissa.cbegin(), iter);
	}

	int d_exp(int_scale);

	d_exp += exponent;

	int b_exp(0);

	while (d_exp > 0)
		scale_down(m, d_exp, b_exp);

	while (d_exp < 0 || m[0] < (src_num_radix / 2))
		scale_up(m, d_exp, b_exp);

	T val(0);
#if 0
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
#endif
	return val;
}

template <typename T>
void decimal_real_wrapper<T>::scale_down(src_num_type &m, int &d_exp, int &b_exp)
{
	typedef static_table<repository::detail::rec_pow_2<
		long, int, decimal_real_wrapper<T>::src_num_radix
	>> rec_pow_2_;

	typedef static_table<repository::detail::pow_2m1<
		long, int, decimal_real_wrapper<T>::src_num_radix
	>> pow_2m1_;

	int d(d_exp);

	if (d >= int(pow_2m1_::size()))
		d = pow_2m1_::size() - 1;

	int b(pow_2m1_::get_meta<int>(d));

	{
		auto v(pow_2m1_::get(d));

		if (std::lexicographical_compare(
			v.begin(), v.end(),
			m.cbegin(), m.cend(),
			std::less<src_num_type::value_type>()
		))
			--d;
	}

	d_exp -= d;
	b_exp += b;

	auto v(rec_pow_2_::get(d));
	src_num_type w(m.size() + v.size());

	bignum_mul<decimal_real_wrapper<T>::src_num_radix>(w, m, v);

	while (!w.back())
		w.pop_back();

	m.swap(w);
}

template <typename T>
void decimal_real_wrapper<T>::scale_up(
	src_num_type &m, int &d_exp, int &b_exp
)
{
	typedef static_table<repository::detail::rec_pow_2<
		long, int, decimal_real_wrapper<T>::src_num_radix
	>> rec_pow_2_;

	typedef static_table<repository::detail::pow_2<
		long, int, decimal_real_wrapper<T>::src_num_radix
	>> pow_2_;

	int d(-d_exp);
	if (d >= int(rec_pow_2_::size()))
		d = rec_pow_2_::size() - 1;

	int b(rec_pow_2_::get_meta<int>(d));
	auto v(pow_2_::get(d));
	{
		auto v1(rec_pow_2_::get(d));
		if (std::lexicographical_compare(
			m.cbegin(), m.cend(),
			v.begin(), v.end(),
			std::less<src_num_type::value_type>()
		))
			--d;
	}

	b_exp -= b;
	d_exp += d;

	src_num_type w(m.size() + v.size());

	bignum_mul<decimal_real_wrapper<T>::src_num_radix>(w, m, v);

	while (!w.back())
		w.pop_back();

	m.swap(w);
}

#if 0
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
#endif

}
}}}}

#endif
