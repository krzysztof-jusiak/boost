/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_SUPPORT_DETAIL_POW_2_AUG_06_2013_1740)
#define SPIRIT_REPOSITORY_SUPPORT_DETAIL_POW_2_AUG_06_2013_1740

namespace boost { namespace spirit { namespace repository { namespace detail {

template <typename T, typename MetaT, long Radix>
struct pow_2 {
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
pow_2<long, int, 100000000000000000L>::metadata_type const
pow_2<long, int, 100000000000000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 29, 33, 36, 39, 43, 46, 47
};

template <>
pow_2<long, int, 100000000000000000L>::value_type const
pow_2<long, int, 100000000000000000L>::data[] = {
	20000000000000000L, /* 1 */
	80000000000000000L, /* 3 */
	64000000000000000L, /* 6 */
	51200000000000000L, /* 9 */
	81920000000000000L, /* 13 */
	65536000000000000L, /* 16 */
	52428800000000000L, /* 19 */
	83886080000000000L, /* 23 */
	67108864000000000L, /* 26 */
	53687091200000000L, /* 29 */
	85899345920000000L, /* 33 */
	68719476736000000L, /* 36 */
	54975581388800000L, /* 39 */
	87960930222080000L, /* 43 */
	70368744177664000L, /* 46 */
	14073748835532800L  /* 47 */
};

template <>
pow_2<long, int, 100000000000000000L>::selector_type const
pow_2<long, int, 100000000000000000L>::selector[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
};

template <>
std::size_t const
pow_2<long, int, 1000000000000000000L>::size = 16;

#else

template <>
pow_2<long, int, 100000000L>::metadata_type const
pow_2<long, int, 100000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 29, 33, 36, 39, 43, 46, 47
};

template <>
pow_2<long, int, 100000000L>::value_type const
pow_2<long, int, 100000000L>::data[] = {
	20000000L, /* 1 */
	80000000L, /* 3 */
	64000000L, /* 6 */
	51200000L, /* 9 */
	81920000L, /* 13 */
	65536000L, /* 16 */
	52428800L, /* 19 */
	83886080L, /* 23 */
	67108864L, /* 26 */
	20000000L, 53687091L, /* 29 */
	92000000L, 85899345L, /* 33 */
	73600000L, 68719476L, /* 36 */
	38880000L, 54975581L, /* 39 */
	22208000L, 87960930L, /* 43 */
	17766400L, 70368744L, /* 46 */
	83553280L, 14073748L  /* 47 */
};

template <>
pow_2<long, int, 100000000L>::selector_type const
pow_2<long, int, 100000000L>::selector[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13, 15, 17, 19, 21, 23
};

template <>
std::size_t const
pow_2<long, int, 100000000L>::size = 16;

#endif

}}}}

#endif
