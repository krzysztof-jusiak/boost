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

template <int Shift, unsigned long RD0, unsigned long RD1>
unsigned long dbl_div_step(std::pair<unsigned long, unsigned long> x)
{
	constexpr int const word_shift(sizeof(unsigned long) * 8);

#if defined(__LP64__)
	unsigned __int128 w0(x.first);
#else
	unsigned long long w0(x.first);
#endif

	w0 *= RD0;
	decltype(w0) w1(
		x.first < x.second ? x.second - x.first : x.first - x.second
	);
	w1 *= RD0 < RD1 ? RD1 - RD0 : RD0 - RD1;
	decltype(w0) w2(x.second);
	w2 *= RD1;

	if ((x.first < x.second) != (RD0 < RD1))
		w1 += w2 + w0;
	else
		w1 = w2 + w0 - w1;

	unsigned long acc[4];
	acc[0] = w0;
	w1 += w0 >> word_shift;

	acc[1] = w1;
	w2 += w1 >> word_shift;

	acc[2] = w2;
	acc[3] = w2 >> word_shift;

	unsigned long rv;

	if ((Shift / word_shift) < 3) {
		rv = acc[(Shift / word_shift) + 1];
		rv <<= word_shift - (Shift % word_shift);
		rv |= acc[Shift / word_shift] >> (Shift % word_shift);
	} else
		rv = acc[3] >> (Shift % word_shift);

	return rv;

}

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

	constexpr int const word_shift(sizeof(unsigned long) * 8);

#if defined(__LP64__)
	unsigned __int128 prod(u);
#else
	unsigned long long prod(u);
#endif

	prod *= v;
	prod += k;

	std::pair<unsigned long, unsigned long> rv;

	rv.second = dbl_div_step<
		mpl::x11::at_c<magic_values, 0>::type::value,
		mpl::x11::at_c<magic_values, 1>::type::value,
		mpl::x11::at_c<magic_values, 2>::type::value
	>(std::make_pair(
		static_cast<unsigned long>(prod),
		static_cast<unsigned long>(prod >> word_shift)
	));

	decltype(prod) r(rv.second);
	r *= Radix;
	r = prod - r;
	rv.first = static_cast<unsigned long>(r);

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
