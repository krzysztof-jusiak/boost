/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_SUPPORT_DETAIL_POW_2M1_JUL_29_2013_1800)
#define SPIRIT_REPOSITORY_SUPPORT_DETAIL_POW_2M1_JUL_29_2013_1800

namespace boost { namespace spirit { namespace repository { namespace detail {

template <typename T, typename MetaT, long Radix>
struct pow_2m1 {
	typedef T value_type;
	typedef MetaT metadata_type;
	typedef unsigned short selector_type;

	static metadata_type const metadata[];
	static value_type const data[];
	static selector_type const selector[];

	static std::size_t const size;
};

#if defined(__LP64__)

template <>
pow_2m1<long, int, 100000000000000000L>::metadata_type const
pow_2m1<long, int, 100000000000000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 29, 33, 36, 39, 43, 46, 47
};

template <>
pow_2m1<long, int, 100000000000000000L>::value_type const
pow_2m1<long, int, 100000000000000000L>::data[] = {
	10000000000000000L, /* 1 */
	70000000000000000L, /* 3 */
	63000000000000000L, /* 6 */
	51100000000000000L, /* 9 */
	81910000000000000L, /* 13 */
	65535000000000000L, /* 16 */
	52428700000000000L, /* 19 */
	83886070000000000L, /* 23 */
	67108863000000000L, /* 26 */
	53687091100000000L, /* 29 */
	85899345910000000L, /* 33 */
	68719476735000000L, /* 36 */
	54975581388700000L, /* 39 */
	87960930222070000L, /* 43 */
	70368744177663000L, /* 46 */
	14073748835532700L  /* 47 */
};

template <>
pow_2m1<long, int, 100000000000000000L>::selector_type const
pow_2m1<long, int, 100000000000000000L>::selector[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
};

template <>
std::size_t const
pow_2m1<long, int, 100000000000000000L>::size = 16;

#else

template <>
pow_2m1<long, int, 100000000L>::metadata_type const
pow_2m1<long, int, 100000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 29, 33, 36, 39, 43, 46, 47
};

template <>
pow_2m1<long, int, 100000000L>::value_type const
pow_2m1<long, int, 100000000L>::data[] = {
	10000000L, /* 1 */
	70000000L, /* 3 */
	63000000L, /* 6 */
	51100000L, /* 9 */
	81910000L, /* 13 */
	65535000L, /* 16 */
	52428700L, /* 19 */
	83886070L, /* 23 */
	67108863L, /* 26 */
	10000000L, 53687091L, /* 29 */
	91000000L, 85899345L, /* 33 */
	73500000L, 68719476L, /* 36 */
	38870000L, 54975581L, /* 39 */
	22207000L, 87960930L, /* 43 */
	17766300L, 70368744L, /* 46 */
	83553270L, 14073748L  /* 47 */
};

template <>
pow_2m1<long, int, 100000000L>::selector_type const
pow_2m1<long, int, 100000000L>::selector[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13, 15, 17, 19, 21, 23
};

template <>
std::size_t const
pow_2m1<long, int, 100000000L>::size = 16;

#endif

}}}}

#endif
