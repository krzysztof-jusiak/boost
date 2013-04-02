/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ARITHMETIC_APR_01_2013_2300)
#define MPL_X11_ARITHMETIC_APR_01_2013_2300

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mpl/detail/largest_int.hpp>

#if defined(BOOST_TEST_MODULE)
#include_next <boost/mpl/arithmetic.hpp>
#endif

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct plus;

template <>
struct plus<> : std::false_type
{};

template <typename T>
struct plus<T> : T
{};

template <typename T1, typename T2>
struct plus<T1, T2>
: std::integral_constant<
	typename detail::largest_int<
		typename T1::value_type, typename T2::value_type
	>::type, T1::value + T2::value
>
{};

template <typename T1, typename T2, typename... Tn>
struct plus<T1, T2, Tn...>
: std::integral_constant<
	typename detail::largest_int<
		typename T1::value_type, typename plus<T2, Tn...>::value_type
	>::type, T1::value + plus<T2, Tn...>::value
>
{};

template <typename T>
using negate = std::integral_constant<typename T::value_type, -(T::value)>;

}}}

#endif
