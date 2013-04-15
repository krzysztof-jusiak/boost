/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_VOID_APR_03_2013_1445)
#define MPL_X11_VOID_APR_03_2013_1445

#include <boost/mpl/x11/integral.hpp>

namespace boost { namespace mpl { namespace x11 {

struct void_ {
	typedef void_ type;
};

template <typename T>
struct is_void_ : false_type {};

template <> struct is_void_<void_> : true_type {};

template <typename T>
struct is_not_void_ : true_type {};

template <> struct is_not_void_<void_> : false_type {};

}}}

#endif
