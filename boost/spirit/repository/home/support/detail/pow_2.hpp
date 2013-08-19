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
pow_2<long, int, 1000000000000000000L>::metadata_type const
pow_2<long, int, 1000000000000000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 27
};

template <>
pow_2<long, int, 1000000000000000000L>::value_type const
pow_2<long, int, 1000000000000000000L>::data[] = {
	200000000000000000L, /* 1 */
	800000000000000000L, /* 3 */
	640000000000000000L, /* 6 */
	512000000000000000L, /* 9 */
	819200000000000000L, /* 13 */
	655360000000000000L, /* 16 */
	524288000000000000L, /* 19 */
	838860800000000000L, /* 23 */
	671088640000000000L, /* 26 */
	134217728000000000L  /* 27 */
	#if 0
	536870912000000000L, /* 29 */
	858993459200000000L, /* 33 */
	687194767360000000L, /* 36 */
	549755813888000000L, /* 39 */
	879609302220800000L, /* 43 */
	703687441776640000L, /* 46 */
	562949953421312000L  /* 49 */
	#endif
};


template <>
pow_2<long, int, 1000000000000000000L>::selector_type const
pow_2<long, int, 1000000000000000000L>::selector[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

template <>
std::size_t const
pow_2<long, int, 1000000000000000000L>::size = 10;

#else

template <>
pow_2<long, int, 1000000000L>::metadata_type const
pow_2<long, int, 1000000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 29, 33, 36, 39, 43, 46, 49
};

template <>
pow_2<long, int, 1000000000L>::value_type const
pow_2<long, int, 1000000000L>::data[] = {
	200000000L, /* 1 */
	800000000L, /* 3 */
	640000000L, /* 6 */
	512000000L, /* 9 */
	819200000L, /* 13 */
	655360000L, /* 16 */
	524288000L, /* 19 */
	838860800L, /* 23 */
	671088640L, /* 26 */
	536870912L, /* 29 */
	858993459L, 200000000L, /* 33 */
	687194767L, 360000000L, /* 36 */
	549755813L, 888000000L, /* 39 */
	879609302L, 220800000L, /* 43 */
	703687441L, 776640000L, /* 46 */
	562949953L, 421312000L  /* 49 */
};

template <>
pow_2<long, int, 1000000000L>::selector_type const
pow_2<long, int, 1000000000L>::selector[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 22
};

template <>
std::size_t const
pow_2<long, int, 1000000000000000000L>::size = 16;

#endif

}}}}

#endif
