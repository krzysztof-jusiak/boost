/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ARITHMETIC_APR_01_2013_2300)
#define MPL_X11_ARITHMETIC_APR_01_2013_2300

#include <boost/mpl/x11/detail/largest_int.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct plus;

template <>
struct plus<> : std::false_type
{};

template <typename T0>
struct plus<T0> : T0
{};

template <typename T0, typename T1>
struct plus<T0, T1>
: std::integral_constant<
	typename detail::largest_int<
		typename T0::value_type, typename T1::value_type
	>::type, T0::value + T1::value
>
{};

template <typename T0, typename T1, typename... Tn>
struct plus<T0, T1, Tn...>
: std::integral_constant<
	typename detail::largest_int<
		typename T0::value_type, typename plus<T1, Tn...>::value_type
	>::type, T0::value + plus<T1, Tn...>::value
>
{};

template <typename T>
using negate = std::integral_constant<typename T::value_type, -(T::value)>;

template <typename T>
using increment = std::integral_constant<
	typename T::value_type, (T::value + 1)
>;

template <typename T>
using decrement = std::integral_constant<
	typename T::value_type, (T::value - 1)
>;


}}}

#endif
