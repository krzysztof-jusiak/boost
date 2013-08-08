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
	long Radix, typename OutputRange, typename InputRangeU,
	typename InputRangeV
> void bignum_mul(OutputRange &w, InputRangeU const &u, InputRangeV const &v)
{
	std::fill(w.begin() + u.size(), w.end(), 0UL);

	for (auto j(v.size());  j > 0; --j) {
		if (!v[j - 1]) {
			w[j - 1] = 0;
			continue;
		}
		std::pair<unsigned long, unsigned long> k(0, 0);
		for (auto i(u.size()); i > 0; --i) {
			k = detail::bignum_mul_step<Radix>(
				w[i + j - 1], k.second, u[i - 1], v[j - 1]
			);
			w[i + j - 1] = k.first;
		}

		w[j - 1] = k.second;
	}
}

}}}

#endif
