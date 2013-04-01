/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_OR_MAR_31_2013_2300)
#define MPL_X11_OR_MAR_31_2013_2300

#if defined(_MSC_VER)
#pragma once
#endif

#include <type_traits>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct or_;

template <>
struct or_<> : mpl::true_
{};

template<typename T1>
struct or_<T1> : T1
{};

template<typename T1, typename T2>
struct or_<T1, T2> : std::conditional<T1::value, T1, T2>::type
{};

template<typename T1, typename T2, typename T3, typename... Tn>
struct or_<T1, T2, T3, Tn...>
: std::conditional<T1::value, T1, or_<T2, T3, Tn...>>::type
{};

}}}

#endif
