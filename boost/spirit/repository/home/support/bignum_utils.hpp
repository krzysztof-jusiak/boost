/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    Based on algorithms from section 4.3.1 of TAoCP by D. Knuth.
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_SUPPORT_BIGNUM_UTILS_JUL_27_2013_1830)
#define SPIRIT_REPOSITORY_SUPPORT_BIGNUM_UTILS_JUL_27_2013_1830

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/mpl/x11/has_key.hpp>
#include <boost/mpl/x11/vector.hpp>
#include <boost/mpl/x11/map.hpp>
#include <boost/mpl/x11/at.hpp>

namespace boost { namespace spirit { namespace repository {
namespace detail {

#if defined(__LP64__)

typedef mpl::x11::map<
	mpl::x11::pair<
		mpl::x11::long_<100000000000000000L>,
		mpl::x11::vector<
			mpl::x11::int_<184>,
			mpl::x11::ulong_<0x9befeb9fad487c3UL>,
			mpl::x11::ulong_<0xb877aa3236a4b449UL>
		>
	>
> magic_multipliers;

#else

typedef mpl::x11::map<
	mpl::x11::pair<
		mpl::x11::long_<100000000L>,
		mpl::x11::vector<
			mpl::x11::int_<90>,
			mpl::x11::ulong_<0x8461cefdUL>,
			mpl::x11::ulong_<0xabcc7711UL>
		>
	>
> magic_multipliers;

#endif

template <long Radix>
typename std::enable_if<
	mpl::x11::has_key<
		magic_multipliers, mpl::x11::long_<Radix>
	>::value, std::pair<unsigned long, unsigned long>
>::type bignum_mul_step(
	unsigned long k, unsigned long u, unsigned long v
)
{

	if (!(u && v))
		return std::make_pair(k % Radix, k / Radix);

	typedef typename mpl::x11::at<
		magic_multipliers,
		mpl::x11::long_<Radix>
	>::type magic_values;

	constexpr int const word_shift(
		std::numeric_limits<unsigned long>::digits
	);
	constexpr int const word_offset(
		mpl::x11::at_c<magic_values, 0>::type::value
		/ word_shift
	);
	constexpr int const subword_shift(
		mpl::x11::at_c<magic_values, 0>::type::value
		% word_shift
	);
	constexpr unsigned long const m[2] = {
		mpl::x11::at_c<magic_values, 1>::type::value,
		mpl::x11::at_c<magic_values, 2>::type::value
	};

#if defined(__LP64__)
	unsigned __int128 prod(u);
#else
	unsigned long long prod(u);
#endif

	prod *= v;
	prod += k;

	unsigned long x[2] = {
		static_cast<unsigned long>(prod),
		static_cast<unsigned long>(prod >> word_shift)
	};
	unsigned long y[4];

	decltype(prod) w0(x[0]);
	w0 *= m[0];
	decltype(prod) w1(x[0] < x[1] ? x[1] - x[0] : x[0] - x[1]);
	w1 *= m[0] < m[1] ? m[1] - m[0] : m[0] - m[1];
	decltype(prod) w2(x[1]);
	w2 *= m[1];

	if ((x[0] < x[1]) != (m[0] < m[1]))
		w1 += w2 + w0;
	else
		w1 = w2 + w0 - w1;

	y[0] = w0;
	w1 += w0 >> word_shift;

	y[1] = w1;
	w2 += w1 >> word_shift;

	y[2] = w2;
	y[3] = w2 >> word_shift;

	std::pair<unsigned long, unsigned long> rv;

	if (word_offset < 3) {
		rv.second = y[word_offset + 1];
		rv.second <<= word_shift - subword_shift;
		rv.second |= y[word_offset] >> subword_shift;
	} else
		rv.second = y[3] >> subword_shift;

	w0 = rv.second;
	w0 *= Radix;
	w0 = prod - w0;
	rv.first = static_cast<unsigned long>(w0);

	return rv;
}

template <long Radix>
typename std::enable_if<
	!mpl::x11::has_key<
		magic_multipliers, mpl::x11::long_<Radix>
	>::value, std::pair<unsigned long, unsigned long>
>::type bignum_mul_step(
	unsigned long k, unsigned long u, unsigned long v
)
{
	if (!(u && v))
		return std::make_pair(k % Radix, k / Radix);

#if defined(__LP64__)
	unsigned __int128 acc(u);
#else
	unsigned long long acc(u);
#endif
	acc *= v;
	acc += k;

	return std::make_pair(acc % Radix, acc / Radix);
}

}

template <
	long Radix, typename OutputRange, typename InputRangeU
> void bignum_mul_s(
	OutputRange &w, InputRangeU const &u,
	typename InputRangeU::value_type v
)
{
	if (!v) {
		std::fill(w.begin(), w.end(), 0);
		return;
	}

	std::pair<unsigned long, unsigned long> c(0, 0);
	auto w_iter(w.begin());

	for (auto up : u) {
		c = detail::bignum_mul_step<Radix>(
			c.second, up, v
		);
		*w_iter = c.first;
		++w_iter;
	}
	*w_iter = c.second;
}

/* w is expected to have a "leading" zero location in the most significant
 * (back()) position.
 */
template <
	long Radix, typename InputOutputRange
> void bignum_mul_si(
	InputOutputRange &w, typename InputOutputRange::value_type v
)
{
	if (!v) {
		std::fill(w.begin(), w.end(), 0);
		return;
	}

	std::pair<unsigned long, unsigned long> c(0, 0);
	for (auto w_iter(w.begin()); w_iter != w.rbegin().base(); ++w_iter) {
		c = detail::bignum_mul_step<Radix>(
			c.second, *w_iter, v
		);
		*w_iter = c.first;
	}
	w.back() = c.second;
}

template <
	long Radix, typename OutputRange, typename InputRangeU,
	typename InputRangeV
> void bignum_mul(OutputRange &w, InputRangeU const &u, InputRangeV const &v)
{
	std::fill(w.begin(), w.end() - v.size(), 0);

	auto w_iter_v(w.begin()), w_iter_u(w.begin());

	for (auto vp : v) {
		if (!vp) {
			*w_iter_v = 0;
			++w_iter_v;
			continue;
		}

		w_iter_u = w_iter_v;
		std::pair<unsigned long, unsigned long> c(0, 0);
		for (auto up : u) {
			c = detail::bignum_mul_step<Radix>(
				*w_iter_u + c.second, up, vp
			);
			*w_iter_u = c.first;
			++w_iter_u;
		}
		*w_iter_u = c.second;
		++w_iter_v;
	}
}

}}}

#endif
