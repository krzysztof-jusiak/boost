/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy 2000-2004
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_LARGEST_INT_APR_01_2013_2300)
#define MPL_X11_DETAIL_LARGEST_INT_APR_01_2013_2300

#if defined(_MSC_VER)
#pragma once
#endif

#include <type_traits>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename T>
struct integral_rank;

template <> struct integral_rank<bool>
: std::integral_constant<int, 1> {};
template <> struct integral_rank<signed char>
: std::integral_constant<int, 2> {};
template <> struct integral_rank<char>
: std::integral_constant<int, 3> {};
template <> struct integral_rank<unsigned char>
: std::integral_constant<int, 4> {};
template <> struct integral_rank<wchar_t>
: std::integral_constant<int, 5> {};
template <> struct integral_rank<short>
: std::integral_constant<int, 6> {};
template <> struct integral_rank<unsigned short>
: std::integral_constant<int, 7> {};
template <> struct integral_rank<int>
: std::integral_constant<int, 8> {};
template <> struct integral_rank<unsigned int>
: std::integral_constant<int, 9> {};
template <> struct integral_rank<long>
: std::integral_constant<int, 10> {};
template <> struct integral_rank<unsigned long>
: std::integral_constant<int, 11> {};
template <> struct integral_rank<long long>
: std::integral_constant<int, 12> {};
template <> struct integral_rank<unsigned long long>
: std::integral_constant<int, 13> {};

template <typename...>
struct largest_int;

template <>
struct largest_int<> {
	typedef bool type;
};

template <typename T>
struct largest_int<T> {
	typedef T type;
};

template <typename T1, typename T2>
struct largest_int<T1, T2> {
	typedef typename std::conditional<
		integral_rank<T1>::value >= integral_rank<T2>::value,
		T1, T2
	>::type type;
};

template <typename T1, typename T2, typename... Tn>
struct largest_int<T1, T2, Tn...> {
	typedef typename std::conditional<
		integral_rank<T1>::value
		>= integral_rank<
			typename largest_int<T2, Tn...>::type
		>::value,
		T1, typename largest_int<T2, Tn...>::type
	>::type type;
};

}}}}

#endif
