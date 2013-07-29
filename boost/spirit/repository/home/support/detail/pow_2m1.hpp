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

	struct selector_type {
		value_type const *ptr;
		MetaT const meta;
	};

	static value_type const data[];
	static selector_type const selector[];

	static constexpr std::size_t size()
	{
		return sizeof(selector) / sizeof(selector_type);
	}
};

#if defined(__LP64__)

template <>
pow_2m1<long, int, 1000000000000000000L>::value_type const
pow_2m1<long, int, 1000000000000000000L>::data[] = {
	0L,
	700000000000000000L, /* 3 */
	630000000000000000L, /* 6 */
	511000000000000000L, /* 9 */
	819100000000000000L, /* 13 */
	655350000000000000L, /* 16 */
	524287000000000000L, /* 19 */
	838860700000000000L, /* 23 */
	671088630000000000L, /* 26 */
	536870911000000000L, /* 29 */
	858993459100000000L, /* 33 */
	687194767350000000L, /* 36 */
	549755813887000000L, /* 39 */
	879609302220700000L, /* 43 */
	703687441776630000L, /* 46 */
	562949953421311000L  /* 49 */
};

template <>
pow_2m1<long, int, 1000000000000000000L>::selector_type const
pow_2m1<long, int, 1000000000000000000L>::selector[] = {
	{ &data[0],  0  },
	{ &data[1],  3  },
	{ &data[2],  6  },
	{ &data[3],  9  },
	{ &data[4],  13 },
	{ &data[5],  16 },
	{ &data[6],  19 },
	{ &data[7],  23 },
	{ &data[8],  26 },
	{ &data[9],  29 },
	{ &data[10], 33 },
	{ &data[11], 36 },
	{ &data[12], 39 },
	{ &data[13], 43 },
	{ &data[14], 46 },
	{ &data[15], 49 },
	{ &data[16], 53 },
	{ &data[17], 0  }
};

#else

template <>
pow_2m1<long, int, 1000000000L>::value_type const
pow_2m1<long, int, 1000000000L>::data[] = {
	0L,
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
	{ &data[0],  0  },
	{ &data[1],  3  },
	{ &data[2],  6  },
	{ &data[3],  9  },
	{ &data[4],  13 },
	{ &data[5],  16 },
	{ &data[6],  19 },
	{ &data[7],  23 },
	{ &data[8],  26 },
	{ &data[9],  29 },
	{ &data[10], 33 },
	{ &data[12], 36 },
	{ &data[14], 39 },
	{ &data[16], 43 },
	{ &data[18], 46 },
	{ &data[20], 49 },
	{ &data[22], 53 },
	{ &data[24], 0  }
};

#endif

}}}}

#endif
