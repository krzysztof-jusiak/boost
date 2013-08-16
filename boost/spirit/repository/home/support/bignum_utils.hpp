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
	std::fill(w.begin() + u.size(), w.end(), 0UL);

	if (!v)
		return;

	std::pair<unsigned long, unsigned long> c(0, 0);
	for (auto i(u.size()); i > 0; --i) {
		c = detail::bignum_mul_step<Radix>(
			*(w.begin() + i), c.second, *(u.begin() + i - 1), v
		);
		*(w.begin() + i) = c.first;
	}

	*w.begin() = c.second;
}

template <
	long Radix, typename OutputRange, typename InputRangeU,
	typename InputRangeV
> void bignum_mul(OutputRange &w, InputRangeU const &u, InputRangeV const &v)
{
	std::fill(w.begin() + u.size(), w.end(), 0UL);

	for (auto j(v.size()); j > 0; --j) {
		if (!*(v.begin() + j - 1)) {
			*(w.begin() + j - 1) = 0;
			continue;
		}
		std::pair<unsigned long, unsigned long> c(0, 0);
		for (auto i(u.size()); i > 0; --i) {
			c = detail::bignum_mul_step<Radix>(
				*(w.begin() + i + j - 1),
				c.second, *(u.begin() + i - 1),
				*(v.begin() + j - 1)
			);
			*(w.begin() + i + j - 1) = c.first;
		}

		*(w.begin() + j - 1) = c.second;
	}
}

}}}

#endif
