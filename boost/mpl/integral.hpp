/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_INTEGRAL_APR_02_2013_1615)
#define MPL_X11_INTEGRAL_APR_02_2013_1615

#if defined(_MSC_VER)
#pragma once
#endif

#include <type_traits>

#if defined(BOOST_TEST_MODULE)
#include <boost/mpl/int.hpp>
#include <boost/mpl/long.hpp>
#endif

namespace boost { namespace mpl { namespace x11 {

template <int value>
using int_ = std::integral_constant<int, value>;

template <long value>
using long_ = std::integral_constant<long, value>;

}}}

#endif
