/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_LOGICAL_MAR_31_2013_2300)
#define MPL_X11_LOGICAL_MAR_31_2013_2300

#if defined(_MSC_VER)
#pragma once
#endif

#if defined(BOOST_TEST_MODULE)
#include_next <boost/mpl/logical.hpp>
#endif

#include <type_traits>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct or_;

template <>
struct or_<> : std::true_type
{};

template <typename T>
struct or_<T> : T
{};

template <typename T1, typename T2>
struct or_<T1, T2> : std::conditional<T1::value, T1, T2>::type
{};

template <typename T1, typename T2, typename... Tn>
struct or_<T1, T2, Tn...>
: std::conditional<T1::value, T1, or_<T2, Tn...>>::type
{};

template <typename...>
struct and_;

template <>
struct and_<> : std::true_type
{};

template <typename T>
struct and_<T> : T
{};

template <typename T1, typename T2>
struct and_<T1, T2> : std::conditional<T1::value, T2, T1>::type
{};

template <typename T1, typename T2, typename... Tn>
struct and_<T1, T2, Tn...>
: std::conditional<T1::value, and_<T2, Tn...>, T1>::type
{};

template <typename T>
using not_ = std::integral_constant<bool, !T::value>;

}}}

#endif
