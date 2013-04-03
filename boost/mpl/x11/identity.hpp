/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_IDENTITY_APR_03_2013_1700)
#define MPL_X11_IDENTITY_APR_03_2013_1700

namespace boost { namespace mpl { namespace x11 {

template <typename T>
struct identity {
	typedef T type;
};

template <typename T>
struct make_identity {
	typedef identity<T> type;
};

}}}

#endif
