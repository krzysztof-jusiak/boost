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
#include <deque>
#include <initializer_list>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename T>
struct decimal_real_wrapper {
	typedef decimal_real_wrapper<T> wrapper_type;
	typedef std::deque<long> src_num_type;

	constexpr static int mantissa_bits = std::numeric_limits<T>::digits;

	/* Leave some room for carry. */
	constexpr static int word_bits
	= std::numeric_limits<long>::digits - 3;

	constexpr static int bigint_words
	= (mantissa_bits + word_bits + 1) / word_bits;

	typedef std::array<long, bigint_words> dst_num_type;

	/* Least significant value bit in the bigint expansion. */
	constexpr static unsigned long sig_bit_mask
	= 1UL << (bigint_words * word_bits - mantissa_bits);

#ifdef __LP64__
	constexpr static long src_num_radix = 100000000000000000L;
#else
	constexpr static long src_num_radix = 100000000L;
#endif

	src_num_type mantissa;
	bool sign;
	long back_scale;
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

	static void src_to_dst_num_type(
		dst_num_type &high, dst_num_type &low, src_num_type const &m
	);
	static void src_to_dst_num_type(
		dst_num_type &dst, src_num_type const &src, T error
	);
	static void average(
		dst_num_type &mid, dst_num_type const &high,
		dst_num_type const &low
	);
	static bool assign_cmp(
		dst_num_type &dst, dst_num_type const &src
	);
	static void normalize(src_num_type &val);
	static void normalize(dst_num_type &val);
	static int target_cmp(
		src_num_type &delta, dst_num_type const &val,
		src_num_type const &m
	);
	static int target_cmp(
		dst_num_type const &val, src_num_type const &m
	);
};

template <typename T>
constexpr int decimal_real_wrapper<T>::word_bits;

template <typename T>
void print(typename decimal_real_wrapper<T>::src_num_type const &m)
{
	bool delim(false);
	for (auto v : m) {
		if (delim)
			printf("_");;
		delim = true;
		printf("%08ld", v);
	}
}

template <typename T>
void print(typename decimal_real_wrapper<T>::dst_num_type const &m)
{
	bool delim(false);
	for (auto v : m) {
		if (delim)
			printf("_");;
		delim = true;
		printf("%07lx", v);
	}
}

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

	dst_num_type low, mid, high;
	src_num_type dx;
	T err(0);
	src_to_dst_num_type(mid, m, err);
	auto c(target_cmp(dx, mid, m));

	if (c)
		for (auto iter(dx.crbegin()); iter != dx.crend(); ++iter) {
			err += *iter;
			err /= src_num_radix;
		}

	if (c > 0) {
		std::copy(mid.cbegin(), mid.cend(), low.begin());
		src_to_dst_num_type(high, m, err);
	} else if (c < 0) {
		std::copy(mid.cbegin(), mid.cend(), high.begin());
		src_to_dst_num_type(low, m, -err);
	}
	
	if (!c || std::equal(low.cbegin(), low.cend(), high.cbegin())) {
		auto tail(mid.back() & (sig_bit_mask - 1UL));
		if (
			tail == (sig_bit_mask >> 1)
			&& !(mid.back() & sig_bit_mask)
		)
			mid.back() -= tail;

		goto skip_search;
	}

	while (true) {
		average(mid, high, low);
		c = target_cmp(mid, m);

		if (c > 0) {
			if (assign_cmp(low, mid))
				break;
		} else if (c < 0)
			assign_cmp(high, mid);
		else {
			auto tail(mid.back() & (sig_bit_mask - 1UL));
			if (
				tail == (sig_bit_mask >> 1)
				&& !(mid.back() & sig_bit_mask)
			)
				mid.back() -= tail;

			break;
		}
	};
skip_search:
	auto tail(mid.back() & (sig_bit_mask - 1UL));
	mid.back() -= tail;
	if (tail >= (sig_bit_mask >> 1)) {
		mid.back() += sig_bit_mask;
		normalize(mid);
	}

	T val(0);
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
void decimal_real_wrapper<T>::scale_down(
	src_num_type &m, int &d_exp, int &b_exp
)
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

	b_exp += pow_2m1_::template get_meta<int>(d);
	d_exp -= d;

	{
		auto v(pow_2m1_::get(d));

		if (std::lexicographical_compare(
			v.begin(), v.end(),
			m.cbegin(), m.cend()
		))
			++d_exp;
	}

	auto v(rec_pow_2_::get(d));
	src_num_type w(m.size() + v.size());

	bignum_mul<src_num_radix>(w, m, v);

	while (!w.back())
		w.pop_back();

	normalize(w);
	m.swap(w);
}

template <typename T>
void decimal_real_wrapper<T>::scale_up(
	src_num_type &m, int &d_exp, int &b_exp
)
{
	typedef static_table<repository::detail::rec_pow_2<
		long, int, src_num_radix
	>> rec_pow_2_;

	typedef static_table<repository::detail::pow_2<
		long, int, src_num_radix
	>> pow_2_;

	int d(-d_exp);
	if (d >= int(rec_pow_2_::size()))
		d = rec_pow_2_::size() - 1;

	int b(rec_pow_2_::template get_meta<int>(d));
	auto v(pow_2_::get(d));
	{
		auto v1(rec_pow_2_::get(d));
		if (std::lexicographical_compare(
			m.cbegin(), m.cend(),
			v1.begin(), v1.end(),
			std::less<src_num_type::value_type>()
		))
			--d;
	}

	b_exp -= b;
	d_exp += d;

	src_num_type w(m.size() + v.size());

	bignum_mul<src_num_radix>(w, m, v);

	while (!w.back())
		w.pop_back();

	normalize(w);
	m.swap(w);
}

template <typename T>
void decimal_real_wrapper<T>::src_to_dst_num_type(
	dst_num_type &dst, src_num_type const &src, T error
)
{
	T val(0), int_val;
	int exp;

	for (auto iter(src.crbegin()); iter != src.crend(); ++iter) {
		val += *iter;
		val /= src_num_radix;
	}

	val += error;

	if (val < T(1))
		for (auto &v : dst) {
			val = std::frexp(val, &exp);
			val = std::ldexp(val, word_bits);
			val = std::modf(val, &int_val);
			v = std::lrint(int_val);
		}
	else
		std::fill(dst.begin(), dst.end(), (1L << word_bits) - 1L);
}

template <typename T>
void decimal_real_wrapper<T>::average(
	dst_num_type &mid, dst_num_type const &high,
	dst_num_type const &low
)
{
	typename dst_num_type::size_type pos(0);
	typename dst_num_type::value_type c(0);

	for (; pos < mid.size(); ++pos) {
		mid[pos] = high[pos] + low[pos];
		if (c)
			mid[pos] += 1L << word_bits;

		c = mid[pos] & 1L;
		mid[pos] >>= 1;
	}

	c = 0;
	for (--pos; pos; --pos) {
		mid[pos] += c;
		c = mid[pos] >> word_bits;
		mid[pos] &= (1L << word_bits) - 1L;
	}
	mid[0] += c;
}

template <typename T>
bool decimal_real_wrapper<T>::assign_cmp(
	dst_num_type &dst, dst_num_type const &src
)
{
	typename dst_num_type::size_type dst_pos(0);
	bool eq(true);

	for (auto v : src) {
		eq = eq && (dst[dst_pos] == v);
		dst[dst_pos++] = v;
	}

	return eq;
}

template <typename T>
void decimal_real_wrapper<T>::normalize(src_num_type &val)
{
	while (val.front() < (src_num_radix / 10)) {
		std::pair<
			typename src_num_type::value_type,
			typename src_num_type::value_type
		> c(0, 0);
		for (auto i(val.size()); i > 0; --i) {
			c = repository::detail::bignum_mul_step<src_num_radix>(
				0, c.second, val[i - 1], 10
			);
			val[i - 1] = c.first;
		}
	}
}

template <typename T>
void decimal_real_wrapper<T>::normalize(dst_num_type &val)
{
	typename dst_num_type::value_type c(0);

	for (auto pos(val.size() - 1); pos > 0; --pos) {
		val[pos] += c;
		c = val[pos] >> word_bits;
		val[pos] &= (1UL << word_bits) - 1UL;
	}

	val[0] += c;
}

template <typename T>
int decimal_real_wrapper<T>::target_cmp(
	src_num_type &delta, dst_num_type const &val, src_num_type const &m
)
{
	typename src_num_type::size_type src_pos(0);
	src_num_type dst_val_in(val.begin(), val.end());
	src_num_type dst_val_out(val.size() + 1);
	delta.clear();

	do {
		bignum_mul_s<(1L << word_bits)>(
			dst_val_out, dst_val_in, src_num_radix
		);

		delta.push_back(m[src_pos] - dst_val_out[0]);
		if (delta.back())
			goto out;

		++src_pos;
		dst_val_in.assign(dst_val_out.begin() + 1, dst_val_out.end());
	} while (src_pos < m.size());

	while (true) {
		bignum_mul_s<(1L << word_bits)>(
			dst_val_out, dst_val_in, src_num_radix
		);

		if (dst_val_out[0] > 0) {
			delta.push_back(-dst_val_out[0]);
			goto out;
		} else if (std::all_of(
			dst_val_out.begin(), dst_val_out.end(), [](
				typename src_num_type::value_type v_
			) -> bool { return !v_; }
		))
			return 0;
		else
			delta.push_back(0);

		dst_val_in.assign(dst_val_out.begin() + 1, dst_val_out.end());
	}
out:
	typename src_num_type::value_type c(0);

	for (auto iter(delta.rbegin()); iter != delta.rend(); ++iter) {
		*iter -= c;
		c = 0;
		if (*iter < 0) {
			*iter = src_num_radix + *iter;
			c = 1;
		}
	}

	if (c) {
		c = 0;

		if (!*delta.rbegin())
			c = 1;
		else
			*delta.rbegin() = src_num_radix - *delta.rbegin();

		for (
			auto iter(delta.rbegin() + 1);
			iter != delta.rend();
			++iter
		) {
			*iter = src_num_radix - *iter - 1 + c;
			if (*iter > src_num_radix) {
				*iter -= src_num_radix;
				c = 1;
			} else
				c = 0;
		}
		return -1;
	} else
		return 1;
}

template <typename T>
int decimal_real_wrapper<T>::target_cmp(
	dst_num_type const &val, src_num_type const &m
)
{
	typename src_num_type::size_type src_pos(0);
	src_num_type dst_val_in(val.begin(), val.end());
	src_num_type dst_val_out(val.size() + 1);

	do {
		bignum_mul_s<(1L << word_bits)>(
			dst_val_out, dst_val_in, src_num_radix
		);

		if (m[src_pos] > dst_val_out[0])
			return 1;
		else if (m[src_pos] < dst_val_out[0])
			return -1;

		++src_pos;
		dst_val_in.assign(dst_val_out.begin() + 1, dst_val_out.end());
	} while (src_pos < m.size());

	while (true) {
		bignum_mul_s<(1L << word_bits)>(
			dst_val_out, dst_val_in, src_num_radix
		);

		if (dst_val_out[0] > 0) {
			return -1;
		} else if (std::all_of(
			dst_val_out.begin(), dst_val_out.end(), [](
				typename src_num_type::value_type v_
			) -> bool { return !v_; }
		))
			return 0;

		dst_val_in.assign(dst_val_out.begin() + 1, dst_val_out.end());
	}
}

}
}}}}

#endif
