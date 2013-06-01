/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_SUPPORT_RADIX_POW_JUN_01_2013_2300)
#define SPIRIT_REPOSITORY_SUPPORT_RADIX_POW_JUN_01_2013_2300

namespace boost { namespace spirit { namespace repository {

template <typename T, unsigned int Radix>
T radix_pow(unsigned int exponent)
{
	unsigned int static const max_pos
		= 1 << ((sizeof(unsigned int) * 8) - 1);

	T rv(1);
	for (
		unsigned int pos = max_pos >> __builtin_clz(exponent);
		pos; pos >>= 1
	) {
		rv *= rv;
		if (exponent & pos)
			rv *= Radix;
	}
	return rv;
}

}}}

#endif
