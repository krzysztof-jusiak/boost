/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_SUPPORT_DETAIL_REC_POW_2_JUL_25_2013_1700)
#define SPIRIT_REPOSITORY_SUPPORT_DETAIL_REC_POW_2_JUL_25_2013_1700

namespace boost { namespace spirit { namespace repository { namespace detail {

template <typename T, typename MetaT, long Radix>
struct rec_pow_2 {
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
rec_pow_2<long, int, 1000000000000000000L>::value_type const
rec_pow_2<long, int, 1000000000000000000L>::data[] = {
	0L,                  /* 1 */
	125000000000000000L, /* 3 */
	156250000000000000L, /* 6 */
	195312500000000000L, /* 9 */
	122070312500000000L, /* 13 */
	152587890625000000L, /* 16 */
	190734863281250000L, /* 19 */
	119209289550781250L, /* 23 */
	149011611938476562L, 500000000000000000L, /* 26 */
	745058059692382812L, 500000000000000000L  /* 27 */
	#if 0
	186264514923095703L, 125000000000000000L, /* 29 */
	116415321826934814L, 453125000000000000L, /* 33 */
	145519152283668518L,  66406250000000000L, /* 36 */
	181898940354585647L, 583007812500000000L, /* 39 */
	113686837721616029L, 739379882812500000L, /* 43 */
	142108547152020037L, 174224853515625000L, /* 46 */
	177635683940025046L, 467781066894531250L  /* 49 */
	#endif
};

template <>
rec_pow_2<long, int, 1000000000000000000L>::selector_type const
rec_pow_2<long, int, 1000000000000000000L>::selector[] = {
	{ &data[0],  1},
	{ &data[1],  3},
	{ &data[2],  6},
	{ &data[3],  9},
	{ &data[4],  13},
	{ &data[5],  16},
	{ &data[6],  19},
	{ &data[7],  23},
	{ &data[8],  26},
	{ &data[10], 27},
	{ &data[12], 0}
	#if 0
	{ &data[10], 29},
	{ &data[12], 33},
	{ &data[14], 36},
	{ &data[16], 39},
	{ &data[18], 43},
	{ &data[20], 46},
	{ &data[22], 49},
	{ &data[24], 53},
	{ &data[26], 0}
	#endif
};

#else

template <>
rec_pow_2<long, int, 1000000000L>::value_type const
rec_pow_2<long, int, 1000000000L>::data[] = {
	0L,         /* 1 */
	125000000L, /* 3 */
	156250000L, /* 6 */
	195312500L, /* 9 */
	122070312L, 500000000L, /* 13 */
	152587890L, 625000000L, /* 16 */
	190734863L, 281250000L, /* 19 */
	119209289L, 550781250L, /* 23 */
	149011611L, 938476562L, 500000000L, /* 26 */
	186264514L, 923095703L, 125000000L, /* 29 */
	116415321L, 826934814L, 453125000L, /* 33 */
	145519152L, 283668518L, 066406250L, /* 36 */
	181898940L, 354585647L, 583007812L, 500000000L, /* 39 */
	113686837L, 721616029L, 739379882L, 812500000L, /* 43 */
	142108547L, 152020037L, 174224853L, 515625000L, /* 46 */
	177635683L, 940025046L, 467781066L, 894531250L  /* 49 */
};

template <>
rec_pow_2<long, int, 1000000000L>::selector_type const
rec_pow_2<long, int, 1000000000L>::selector[] = {
	{ &data[0],  1},
	{ &data[1],  3},
	{ &data[2],  6},
	{ &data[3],  9},
	{ &data[4],  13},
	{ &data[6],  16},
	{ &data[8],  19},
	{ &data[10], 23},
	{ &data[12], 26},
	{ &data[15], 29},
	{ &data[18], 33},
	{ &data[21], 36},
	{ &data[24], 39},
	{ &data[28], 43},
	{ &data[32], 46},
	{ &data[36], 49},
	{ &data[40], 53},
	{ &data[45], 0}
};

#endif

}}}}

#endif
