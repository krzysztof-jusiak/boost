/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    Based on algorithms from section 4.3.1 of TAoCP by D. Knuth.
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_SUPPORT_BIGNUM_UTILS_JUL_27_2013_1830)
#define SPIRIT_REPOSITORY_SUPPORT_BIGNUM_UTILS_JUL_27_2013_1830

#include <boost/range/iterator_range.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace boost { namespace spirit { namespace repository {
namespace detail {

#if defined(__LP64__)

template <long Radix>
std::pair<unsigned long, unsigned long> bignum_mul_step(
	unsigned long w, unsigned long k, unsigned long u, unsigned long v
)
{
	unsigned __int128 r(u);
	r *= v;
	r += w;
	r += k;

	return std::make_pair(r % Radix, r / Radix);
}

#else

template <long Radix>
std::pair<unsigned long, unsigned long> bignum_mul_step(
	unsigned long w, unsigned long k, unsigned long u, unsigned long v
)
{
	unsigned long long r(u);
	r *= v;
	r += w;
	r += k;

	return std::make_pair(r % Radix, r / Radix);
}

#endif

}

template <
	long Radix, typename OutputRange, typename InputRangeU
> void bignum_mul_s(
	OutputRange &w, InputRangeU const &u,
	typename InputRangeU::value_type v
)
{
	std::fill(w.begin(), w.end(), 0);
	if (!v)
		return;

	std::pair<unsigned long, unsigned long> c(0, 0);
	auto w_iter(w.begin());

	for (auto up : u) {
		c = detail::bignum_mul_step<Radix>(
			*w_iter, c.second, up, v
		);
		*w_iter = c.first;
		++w_iter;
	}
	*w_iter = c.second;
}

template <
	long Radix, typename OutputRange, typename InputRangeU,
	typename InputRangeV
> void bignum_mul(OutputRange &w, InputRangeU const &u, InputRangeV const &v)
{
	std::fill_n(w.begin(), v.size(), 0);

	auto w_iter_v(w.begin()), w_iter_u(w.begin());

	for (auto vp : v) {
		if (!v) {
			*w_iter_v = 0;
			++w_iter_v;
			continue;
		}

		w_iter_u = w_iter_v;
		std::pair<unsigned long, unsigned long> c(0, 0);
		for (auto up : u) {
			c = detail::bignum_mul_step<Radix>(
				*w_iter_u, c.second, up, vp
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
