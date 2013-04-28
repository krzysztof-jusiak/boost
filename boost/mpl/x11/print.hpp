/*==============================================================================
    Copyright (c) 2003      David Abrahams
    Copyright (c) 2004      Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_PRINT_APR_28_2013_2300)
#define MPL_X11_PRINT_APR_28_2013_2300

#include <boost/mpl/x11/identity.hpp>

namespace boost { namespace mpl { namespace x11 {

template <class T>
struct print : identity<T> {
	enum {
		n = sizeof(T) > -1
	};
};

}}}

#endif
