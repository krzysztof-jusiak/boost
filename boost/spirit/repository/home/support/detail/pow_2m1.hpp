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

	static constexpr std::size_t size()
	{
		return (sizeof(selector) / sizeof(selector_type)) - 1;
	}
};

#if defined(__LP64__)

template <>
pow_2m1<long, int, 1000000000000000000L>::metadata_type const
pow_2m1<long, int, 1000000000000000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 27
};

template <>
pow_2m1<long, int, 1000000000000000000L>::value_type const
pow_2m1<long, int, 1000000000000000000L>::data[] = {
	100000000000000000L, /* 1 */
	700000000000000000L, /* 3 */
	630000000000000000L, /* 6 */
	511000000000000000L, /* 9 */
	819100000000000000L, /* 13 */
	655350000000000000L, /* 16 */
	524287000000000000L, /* 19 */
	838860700000000000L, /* 23 */
	671088630000000000L, /* 26 */
	134217727000000000L  /* 27 */
	#if 0
	536870911000000000L, /* 29 */
	858993459100000000L, /* 33 */
	687194767350000000L, /* 36 */
	549755813887000000L, /* 39 */
	879609302220700000L, /* 43 */
	703687441776630000L, /* 46 */
	562949953421311000L  /* 49 */
	#endif
};

template <>
pow_2m1<long, int, 1000000000000000000L>::selector_type const
pow_2m1<long, int, 1000000000000000000L>::selector[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

#else

template <>
pow_2m1<long, int, 1000000000000000000L>::metadata_type const
pow_2m1<long, int, 1000000000000000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 29, 33, 36, 39, 43, 46, 49
};

template <>
pow_2m1<long, int, 1000000000L>::value_type const
pow_2m1<long, int, 1000000000L>::data[] = {
	100000000L, /* 1 */
	700000000L, /* 3 */
	630000000L, /* 6 */
	511000000L, /* 9 */
	819100000L, /* 13 */
	655350000L, /* 16 */
	524287000L, /* 19 */
	838860700L, /* 23 */
	671088630L, /* 26 */
	536870911L, /* 29 */
	858993459L, 100000000L, /* 33 */
	687194767L, 350000000L, /* 36 */
	549755813L, 887000000L, /* 39 */
	879609302L, 220700000L, /* 43 */
	703687441L, 776630000L, /* 46 */
	562949953L, 421311000L  /* 49 */
};

template <>
pow_2m1<long, int, 1000000000L>::selector_type const
pow_2m1<long, int, 1000000000L>::selector[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 22
};

#endif

}}}}

#endif
