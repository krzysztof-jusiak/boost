/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_INTEGRAL_APR_02_2013_1615)
#define MPL_X11_INTEGRAL_APR_02_2013_1615

#include <type_traits>

namespace boost { namespace mpl { namespace x11 {

template <bool value>
using bool_ = std::integral_constant<bool, value>;

template <int value>
using int_ = std::integral_constant<int, value>;

template <long value>
using long_ = std::integral_constant<long, value>;

}}}

#endif
