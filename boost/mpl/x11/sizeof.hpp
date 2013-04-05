/*=============================================================================
    Copyright (c) 2000-2003 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_SIZEOF_APR_05_2013_1530)
#define MPL_X11_SIZEOF_APR_05_2013_1530

#include <type_traits>

namespace boost { namespace mpl { namespace x11 {

template <std::size_t value>
using size_t = std::integral_constant<std::size_t, value>;

template <typename T>
struct sizeof_ : mpl::x11::size_t<sizeof(T)> {};

}}}

#endif
