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
rec_pow_2<long, int, 100000000000000000L>::metadata_type const
rec_pow_2<long, int, 100000000000000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 26, 29, 33, 36, 39, 43, 46, 47
};

template <>
rec_pow_2<long, int, 100000000000000000L>::value_type const
rec_pow_2<long, int, 100000000000000000L>::data[] = {
	0L,                 /* 1 */
	12500000000000000L, /* 3 */
	15625000000000000L, /* 6 */
	19531250000000000L, /* 9 */
	12207031250000000L, /* 13 */
	15258789062500000L, /* 16 */
	19073486328125000L, /* 19 */
	11920928955078125L, /* 23 */
	14901161193847656L, 25000000000000000L, /* 26 */
	18626451492309570L, 31250000000000000L, /* 29 */
	11641532182693481L, 44531250000000000L, /* 33 */
	14551915228366851L, 80664062500000000L, /* 36 */
	18189894035458564L, 75830078125000000L, /* 39 */
	11368683772161602L, 97393798828125000L, /* 43 */
	14210854715202003L, 71742248535156250L, /* 46 */
	71054273576010018L, 58711242675781250L  /* 47 */
};

template <>
rec_pow_2<long, int, 100000000000000000L>::selector_type const
rec_pow_2<long, int, 100000000000000000L>::selector[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 18, 20, 22, 24
};

template <>
std::size_t const
rec_pow_2<long, int, 100000000000000000L>::size = 16;

#else

template <>
rec_pow_2<long, int, 100000000L>::metadata_type const
rec_pow_2<long, int, 100000000L>::metadata[] = {
	1, 3, 6, 9, 13, 16, 19, 23, 24
};

template <>
rec_pow_2<long, int, 100000000L>::value_type const
rec_pow_2<long, int, 100000000L>::data[] = {
	0L,        /* 1 */
	12500000L, /* 3 */
	15625000L, /* 6 */
	19531250L, /* 9 */
	12207031L, 25000000L, /* 13 */
	15258789L,  6250000L, /* 16 */
	19073486L, 32812500L, /* 19 */
	11920928L, 95507812L, 50000000L, /* 23 */
	59604644L, 77539062L, 50000000L  /* 24 */
};

template <>
rec_pow_2<long, int, 100000000L>::selector_type const
rec_pow_2<long, int, 100000000L>::selector[] = {
	0, 1, 2, 3, 4, 6, 8, 10, 13, 16
};

template <>
std::size_t const
rec_pow_2<long, int, 100000000L>::size = 9;

#endif

}}}}

#endif
