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
	{ &data[0],  1  },
	{ &data[1],  3  },
	{ &data[2],  6  },
	{ &data[3],  9  },
	{ &data[4],  13 },
	{ &data[5],  16 },
	{ &data[6],  19 },
	{ &data[7],  23 },
	{ &data[8],  26 },
	{ &data[9],  27 },
	{ &data[10], 0  }
	#if 0
	{ &data[9],  29 },
	{ &data[10], 33 },
	{ &data[11], 36 },
	{ &data[12], 39 },
	{ &data[13], 43 },
	{ &data[14], 46 },
	{ &data[15], 49 },
	{ &data[16], 53 },
	{ &data[17], 0  }
	#endif
};

#else

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
	{ &data[0],  1  },
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
