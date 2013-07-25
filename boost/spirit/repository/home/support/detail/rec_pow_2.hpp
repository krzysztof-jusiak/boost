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
	0L,
	1250000000000000000L, /* 3 */
	1562500000000000000L, /* 6 */
	1953125000000000000L, /* 9 */
	1220703125000000000L, /* 13 */
	1525878906250000000L, /* 16 */
	1907348632812500000L, /* 19 */
	1192092895507812500L, /* 23 */
	1490116119384765625L, /* 26 */
	1862645149230957031L, 2500000000000000000L, /* 29 */
	1164153218269348144L, 5312500000000000000L, /* 33 */
	1455191522836685180L, 6640625000000000000L, /* 36 */
	1818989403545856475L, 8300781250000000000L, /* 39 */
	1136868377216160297L, 3937988281250000000L, /* 43 */
	1421085471520200371L, 7422485351562500000L, /* 46 */
	1776356839400250464L, 6778106689453125000L, /* 49 */
	1110223024625156540L, 4236316680908203125L  /* 53 */
};

template <>
rec_pow_2<long, int, 1000000000000000000L>::selector_type const
rec_pow_2<long, int, 1000000000000000000L>::selector[] = {
	{ &data[0],  0},
	{ &data[1],  3},
	{ &data[2],  6},
	{ &data[3],  9},
	{ &data[4],  13},
	{ &data[5],  16},
	{ &data[6],  19},
	{ &data[7],  23},
	{ &data[8],  26},
	{ &data[9],  29},
	{ &data[11], 33},
	{ &data[13], 36},
	{ &data[15], 39},
	{ &data[17], 43},
	{ &data[19], 46},
	{ &data[21], 49},
	{ &data[23], 53},
	{ &data[25], 0}
};

#else

template <>
rec_pow_2<long, int, 1000000000L>::value_type const
rec_pow_2<long, int, 1000000000L>::data[45] = {
	0L,
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
	177635683L, 940025046L, 467781066L, 894531250L, /* 49 */
	111022302L, 462515654L, 042363166L, 809082031L, 250000000L  /* 53 */
};

template <>
rec_pow_2<long, int, 1000000000L>::selector_type const
rec_pow_2<long, int, 1000000000L>::selector[18] = {
	{ &data[0],  0},
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
