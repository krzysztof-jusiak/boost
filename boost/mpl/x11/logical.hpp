/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_LOGICAL_MAR_31_2013_2300)
#define MPL_X11_LOGICAL_MAR_31_2013_2300

#include <type_traits>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct or_;

template <>
struct or_<> : std::true_type
{};

template <typename T0>
struct or_<T0> : T0
{};

template <typename T0, typename T1>
struct or_<T0, T1> : std::conditional<T0::value, T0, T1>::type
{};

template <typename T0, typename T1, typename... Tn>
struct or_<T0, T1, Tn...>
: std::conditional<T0::value, T0, or_<T1, Tn...>>::type
{};

template <typename...>
struct and_;

template <>
struct and_<> : std::true_type
{};

template <typename T>
struct and_<T> : T
{};

template <typename T0, typename T1>
struct and_<T0, T1> : std::conditional<T0::value, T1, T0>::type
{};

template <typename T0, typename T1, typename... Tn>
struct and_<T0, T1, Tn...>
: std::conditional<T0::value, and_<T1, Tn...>, T0>::type
{};

template <typename T>
using not_ = std::integral_constant<bool, !T::value>;

}}}

#endif
