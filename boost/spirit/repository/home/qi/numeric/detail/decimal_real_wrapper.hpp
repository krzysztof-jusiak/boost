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
#include <boost/spirit/repository/home/support/detail/rec_pow_2.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_utils.hpp>

#include <boost/range/adaptor/reversed.hpp>

#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/reverse.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/reverse_copy.hpp>
#include <boost/range/algorithm_ext/for_each.hpp>
#include <boost/range/algorithm/lexicographical_compare.hpp>

#include <cmath>
#include <array>
#include <deque>
#include <initializer_list>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename T>
struct decimal_real_wrapper {
	typedef decimal_real_wrapper<T> wrapper_type;
	typedef long word_type;
	typedef std::vector<word_type> src_num_type;

	constexpr static int mantissa_bits = std::numeric_limits<T>::digits;

	constexpr static word_type base_src_radix = 10L;

#ifdef __LP64__
	constexpr static word_type src_num_radix = 100000000000000000L;
	constexpr static int word_bits = 57;
#else
	constexpr static word_type src_num_radix = 100000000L;
	constexpr static int word_bits = 27;
#endif

/* clang 3.4 required, gcc works
	constexpr static int word_bits
	= std::numeric_limits<long>::digits
	  - __builtin_clzl(src_num_radix) + 1;
*/

	constexpr static int bigint_words
	= (mantissa_bits + 1) % word_bits
	  ? (mantissa_bits + word_bits + 1) / word_bits
	  : (mantissa_bits + 1) / word_bits;

	typedef std::array<long, bigint_words> dst_num_type;

	/* Least significant value bit in the bigint expansion. */
	constexpr static unsigned long sig_bit_pos
	= bigint_words * word_bits - mantissa_bits;
	constexpr static unsigned long sig_bit_mask
	= 1UL << sig_bit_pos;

	src_num_type mantissa;
	bool sign;
	long back_scale;
	int int_scale;
	int frac_scale;
	int exponent;

	template <bool Negative = false>
	struct fraction_op {
		typedef fraction_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			out.sign = Negative;

			auto d(ascii_digit_value<base_src_radix>(in));
			if (!out.int_scale) {
				if (!d) {
					--out.frac_scale;
					return true;
				} else
					out.int_scale = -1;
			}

			return out.append_digit(d);
		}
	};

	template <bool Negative = false>
	struct integer_op {
		typedef integer_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			out.sign = Negative;

			auto d(ascii_digit_value<base_src_radix>(in));
			if (!out.int_scale && !d)
				return true;

			auto rv(out.append_digit(d));
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
				out.exponent *= base_src_radix;
				out.exponent
				+= ascii_digit_value<base_src_radix>(in);
				return true;
			}
		};

		template <typename CharType>
		struct impl<CharType, true> {
			bool operator()(CharType in, wrapper_type &out)
			{
				out.exponent *= base_src_radix;
				out.exponent
				-= ascii_digit_value<base_src_radix>(in);
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
	  int_scale(0), frac_scale(0), exponent(0)
	{}

	operator T() const;

private:
	struct helper {
		src_num_type m;
		int d_exp;
		int b_exp;

		helper(typename src_num_type::size_type new_cap)
		: b_exp(0)
		{
			m.reserve(new_cap);
			sx.reserve(new_cap);
			sy.reserve(new_cap);
		}

		bool get_dst_range(
			dst_num_type &high, dst_num_type &mid,
			dst_num_type &low
		);

		static void normalize(src_num_type &s);

		void scale_down();
		void scale_up();



	private:
		src_num_type sx;
		src_num_type sy;
		src_num_type sz;
	};

	template <typename U>
	bool append_digit(U d);

	template <typename SrcSeq>
	static void src_to_dst_num_type(
		dst_num_type &dst, SrcSeq const &src
	);
	static void average(
		dst_num_type &mid, dst_num_type const &high,
		dst_num_type const &low
	);
	static typename src_num_type::value_type target_cmp(
		dst_num_type const &dst, src_num_type const &src,
		int &delta_offset
	);
};

template <typename T>
constexpr int decimal_real_wrapper<T>::word_bits;

template <typename Tr, bool Rev = true>
void print(char const *fmt, Tr const &r)
{
	bool delim(false);
	if (Rev)
		for (auto d: r | boost::adaptors::reversed) {
			if (delim)
				printf("_");;
			delim = true;
			printf(fmt, d);
		}
	else
		for (auto d: r) {
			if (delim)
				printf("_");;
			delim = true;
			printf(fmt, d);
		}
	printf("\n");
}

template <typename T>
decimal_real_wrapper<T>::operator T() const
{
	helper h(64);

	for (auto iter(mantissa.crbegin()); iter != mantissa.crend(); ++iter) {
		if (*iter) {
			h.m.resize(iter.base() - mantissa.cbegin());
			std::reverse_copy(
				mantissa.cbegin(),
				mantissa.cbegin() + h.m.size(),
				h.m.begin()
			);
			break;
		}
	}

	if (h.m.empty()) {
		return std::copysign(T(0), sign ? T(-1) : T(1));
	}

	h.d_exp = int_scale > 0 ? int_scale : frac_scale;
	h.d_exp += exponent;
	dst_num_type high, mid, low;
	bool do_search(true);

	if (!h.get_dst_range(high, mid, low)) {
		auto tail(mid.back() & (sig_bit_mask - 1UL));
		if (
			tail == (sig_bit_mask >> 1)
			&& !(mid.back() & sig_bit_mask)
		)
			mid.back() -= tail;

		do_search = false;
	} else if (boost::range::equal(low, high))
		do_search = false;

	while (do_search) {
		average(mid, high, low);
		int d_off(0);
		auto c(target_cmp(mid, h.m, d_off));

		if (c > 0) {
			boost::range::for_each(
				low, mid, [&do_search] (
					typename dst_num_type::value_type &lv,
					typename dst_num_type::value_type &mv
				) {
					do_search = do_search && (lv == mv);
					lv = mv;
				}
			);
			do_search = !do_search;
		} else if (c < 0)
			boost::range::copy(mid, high.begin());
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

	auto tail(mid.back() & (sig_bit_mask - 1UL));
	mid.back() -= tail;
	if (tail >= (sig_bit_mask >> 1)) {
		mid.back() += sig_bit_mask;

		typename dst_num_type::value_type c(0);
		for (
			auto iter(mid.end() - 1);
			iter != (mid.begin()); --iter
		) {
			*iter += c;
			c = (*iter) >> word_bits;
			*iter &= (1UL << word_bits) - 1UL;
		}
		mid.front() += c;
	}

	T val(0);
	for (auto v : mid) {
		val = std::ldexp(val, word_bits);
		val += v;
	}

	return std::copysign(
		std::ldexp(val, h.b_exp - word_bits * mid.size()),
		sign ? T(-1) : T(1)
	);
}

template <typename T>
template <typename U>
bool decimal_real_wrapper<T>::append_digit(U d)
{
	back_scale /= base_src_radix;
	mantissa.back() += back_scale * d;

	if (back_scale == 1L) {
		mantissa.push_back(0);
		back_scale = src_num_radix;
	}
	return true;
}

template <typename T>
bool decimal_real_wrapper<T>::helper::get_dst_range(
	dst_num_type &high, dst_num_type &mid, dst_num_type &low
)
{
	while (d_exp > 0)
		scale_down();

	while (d_exp < 0 || m.back() < (src_num_radix / 2))
		scale_up();

	src_to_dst_num_type(mid, m);

	int delta_off(0);
	auto delta(target_cmp(mid, m, delta_off));

	if (!delta)
		return false;

	typename src_num_type::value_type mx_[m.size()];
	boost::iterator_range<typename src_num_type::value_type *> mx(
		&mx_[0], &mx_[m.size()]
	);

	boost::range::copy(m, mx.begin());
	if (delta_off >= mx.size()) {
		delta_off = mx.size() - 1;
		delta = delta >= 0 ? 1 : -1;
	}

	auto pos(mx.end() - delta_off - 1);
	if (delta > 0) {
		do {
			*pos += delta;
			if (*pos >= src_num_radix) {
				*pos -= src_num_radix;
				delta = 1;
			} else
				break;
		} while (pos++ != mx.end());
		boost::range::copy(mid, low.begin());
		src_to_dst_num_type(high, mx);
	} else {
		do {
			*pos += delta;
			if (*pos < 0) {
				*pos += src_num_radix;
				delta = -1;
			} else
				break;
		} while (pos++ != mx.end());
		boost::range::copy(mid, high.begin());
		src_to_dst_num_type(low, mx);
	}
	return true;
}

template <typename T>
void decimal_real_wrapper<T>::helper::scale_down()
{
	typedef static_table<repository::detail::rec_pow_2<
		long, int, decimal_real_wrapper<T>::src_num_radix
	>> rec_pow_2_;

	typedef static_table<repository::detail::pow_2<
		long, int, src_num_radix
	>> pow_2_;

	int d(d_exp);

	if (d >= int(pow_2_::size()))
		d = pow_2_::size() - 1;

	b_exp += pow_2_::template get_meta<int>(d);
	d_exp -= d;

	if (boost::range::lexicographical_compare(
		pow_2_::get(d) | boost::adaptors::reversed,
		m | boost::adaptors::reversed,
		std::less_equal<typename src_num_type::value_type>()
	))
		++d_exp;

	auto v(rec_pow_2_::get(d));
	sx.resize(m.size() + v.size());
	bignum_mul<src_num_radix>(sx, m, v);
	normalize(sx);
	m.swap(sx);
}

template <typename T>
void decimal_real_wrapper<T>::helper::scale_up()
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

	b_exp -= rec_pow_2_::template get_meta<int>(d);
	d_exp += d;

	if (boost::range::lexicographical_compare(
		m | boost::adaptors::reversed,
		rec_pow_2_::get(d) |  boost::adaptors::reversed
	))
		--d_exp;

	auto v(pow_2_::get(d));
	sx.resize(m.size() + v.size());
	bignum_mul<src_num_radix>(sx, m, v);
	normalize(sx);
	m.swap(sx);
}

template <typename T>
template <typename SrcSeq>
void decimal_real_wrapper<T>::src_to_dst_num_type(
	dst_num_type &dst, SrcSeq const &src
)
{
	constexpr static long r = (1L << word_bits) % src_num_radix;
	static_assert(
		((1L << word_bits) / src_num_radix) == 1L,
		"Destination radix is not tight enough."
	);

	src_num_type::value_type kx, ky;
	std::pair<word_type, word_type> c(0, 0);

	word_type acc[src.size()];
	boost::iterator_range<word_type *> acc_r(
		&acc[0], &acc[src.size()]
	);

	boost::range::copy(src, acc_r.begin());

	for (auto &d: dst) {
		kx = 0;
		for (auto &s: acc_r) {
			ky = s;
			c = repository::detail::bignum_mul_step<
				src_num_radix
			>(c.second + kx, s, r);
			s = c.first;
			kx = ky;
		}
		d = kx + c.second;
	}
}

template <typename T>
void decimal_real_wrapper<T>::average(
	dst_num_type &mid, dst_num_type const &high,
	dst_num_type const &low
)
{
	typename dst_num_type::value_type c(0);

	boost::range::transform(
		low | boost::adaptors::reversed,
		high | boost::adaptors::reversed,
		mid.rbegin(), [&c](
			typename dst_num_type::value_type x,
			typename dst_num_type::value_type y
		) -> typename dst_num_type::value_type {
			c += x + y;
			auto nc(c & ((1UL << word_bits) - 1UL));
			c >>= word_bits;
			return nc;
		}
	);

	for (auto &d: mid) {
		auto nc((c & 1) << (word_bits - 1));
		nc |= d >> 1;
		c = d;
		d = nc;
	}
}

template <typename T>
void decimal_real_wrapper<T>::helper::normalize(src_num_type &s)
{
	if (src_num_radix
	    < (std::numeric_limits<typename src_num_type::value_type>::max()
	       / base_src_radix / 2)
	) {
		while (s.back() < (src_num_radix / base_src_radix)) {
			typename src_num_type::value_type c(0);
			for (auto &d : s) {
				d *= base_src_radix;
				d += c;
				c = d / src_num_radix;
				d %= src_num_radix;
			}
		}
	} else {
		while (s.back() < (src_num_radix / base_src_radix)) {
			std::pair<
				typename src_num_type::value_type,
				typename src_num_type::value_type
			> c(0, 0);
			for (auto &d : s) {
				c = repository::detail::bignum_mul_step<
					src_num_radix
				>(c.second, d, base_src_radix);
				d = c.first;
			}
		}
	}
}

template <typename T>
auto decimal_real_wrapper<T>::target_cmp(
	dst_num_type const &dst, src_num_type const &src, int &delta_offset
) -> typename src_num_type::value_type
{
	typename dst_num_type::value_type acc[dst.size()];
	boost::iterator_range<typename dst_num_type::value_type *> acc_r(
		&acc[0], &acc[dst.size()]
	);

	boost::range::reverse_copy(dst, acc_r.begin());

	for (auto u: src | boost::adaptors::reversed) {
		std::pair<
			typename dst_num_type::value_type,
			typename dst_num_type::value_type
		> c(0, 0);

		for (auto &v: acc_r) {
			c = repository::detail::bignum_mul_step<
				1L << word_bits
			>(c.second, v, src_num_radix);
			v = c.first;
		}

		if (u - c.second)
			return u - c.second;

		++delta_offset;
	}

	while (true) {
		std::pair<
			typename dst_num_type::value_type,
			typename dst_num_type::value_type
		> c(0, 0);

		for (auto &v: acc_r) {
			c = repository::detail::bignum_mul_step<
				1L << word_bits
			>(c.second, v, src_num_radix);
			v = c.first;
		}

		if (c.second) {
			return -c.second;
		} else if (std::all_of(
			acc_r.begin(), acc_r.end(), [](
				typename src_num_type::value_type v
			) -> bool { return !v; }
		))
			return 0;

		++delta_offset;
	}
}
}
}}}}

#endif
