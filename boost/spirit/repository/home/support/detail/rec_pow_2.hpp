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
	typedef MetaT metadata_type;
	typedef unsigned short selector_type;

	static metadata_type const metadata[];
	static value_type const data[];
	static selector_type const selector[];

	static std::size_t const size;
};

#if defined(__LP64__)

template <>
rec_pow_2<long, int, 1000000000000000000L>::metadata_type const
rec_pow_2<long, int, 1000000000000000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 27
};

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
	0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12
};

template <>
std::size_t const
rec_pow_2<long, int, 1000000000000000000L>::size = 10;

#else

template <>
rec_pow_2<long, int, 1000000000L>::metadata_type const
rec_pow_2<long, int, 1000000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 29, 33, 36, 39, 43, 46, 49
};

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
	0, 1, 2, 3, 4, 6, 8, 10, 12, 15, 18, 21, 24, 28, 32, 36, 40
};

template <>
std::size_t const
rec_pow_2<long, int, 1000000000L>::size = 16;

#endif

}}}}

#endif
