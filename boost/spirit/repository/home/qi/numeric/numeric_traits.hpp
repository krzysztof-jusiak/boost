/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_TRAITS_JUN_05_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_TRAITS_JUN_05_2013_2300

#include <boost/spirit/repository/home/support/radix_pow.hpp>

namespace boost { namespace spirit { namespace repository { namespace traits {

template <typename T>
inline T zero()
{
	return 0;
}

template <typename T>
inline void negate(T &n)
{
	n = -n;
}

template <typename T, typename E, unsigned int Radix = 10>
inline bool scale(T &n, E exp)
{
	if (exp >= 0) {
		T m(radix_pow<T, Radix>(exp));
		n *= m;
	} else {
		T m(radix_pow<T, Radix>(-exp));
		n /= m;
	}
	return true;
}

}}}}

#endif
