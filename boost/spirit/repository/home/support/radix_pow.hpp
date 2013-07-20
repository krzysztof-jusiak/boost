/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_SUPPORT_RADIX_POW_JUN_01_2013_2300)
#define SPIRIT_REPOSITORY_SUPPORT_RADIX_POW_JUN_01_2013_2300

namespace boost { namespace spirit { namespace repository {

template <typename T, unsigned long Radix>
T radix_pow(unsigned long exponent) const
{
	static unsigned long constexpr max_pos
	= 1UL << ((std::numeric_limits<unsigned long>::digits) - 1);

	T rv(1);
	for (auto pos = max_pos >> __builtin_clzl(exponent); pos; pos >>= 1) {
		rv *= rv;
		if (exponent & pos)
			rv *= Radix;
	}
	return rv;
}

}}}

#endif
