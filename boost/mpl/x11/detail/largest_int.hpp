/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_LARGEST_INT_APR_01_2013_2300)
#define MPL_X11_DETAIL_LARGEST_INT_APR_01_2013_2300

#include <boost/mpl/x11/integral.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename T>
struct integral_rank;

template <> struct integral_rank<bool>               : int_<1> {};
template <> struct integral_rank<signed char>        : int_<2> {};
template <> struct integral_rank<char>               : int_<3> {};
template <> struct integral_rank<unsigned char>      : int_<4> {};
template <> struct integral_rank<wchar_t>            : int_<5> {};
template <> struct integral_rank<short>              : int_<6> {};
template <> struct integral_rank<unsigned short>     : int_<7> {};
template <> struct integral_rank<int>                : int_<8> {};
template <> struct integral_rank<unsigned int>       : int_<9> {};
template <> struct integral_rank<long>               : int_<10> {};
template <> struct integral_rank<unsigned long>      : int_<11> {};
template <> struct integral_rank<long long>          : int_<12> {};
template <> struct integral_rank<unsigned long long> : int_<13> {};

template <typename...>
struct largest_int;

template <>
struct largest_int<> {
	typedef bool type;
};

template <typename T0>
struct largest_int<T0> {
	typedef T0 type;
};

template <typename T0, typename T1>
struct largest_int<T0, T1> {
	typedef typename std::conditional<
		integral_rank<T0>::value >= integral_rank<T1>::value,
		T0, T1
	>::type type;
};

template <typename T0, typename T1, typename... Tn>
struct largest_int<T0, T1, Tn...> {
	typedef typename std::conditional<
		integral_rank<T0>::value
		>= integral_rank<
			typename largest_int<T1, Tn...>::type
		>::value,
		T0, typename largest_int<T1, Tn...>::type
	>::type type;
};

}}}}

#endif
