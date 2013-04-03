/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_PAIR_APR_03_2013_2250)
#define MPL_X11_PAIR_APR_03_2013_2250

namespace boost { namespace mpl { namespace x11 {

template <typename T0, typename T1>
struct pair {
	typedef pair type;
	typedef T0 first;
	typedef T1 second;
};

template <typename T>
struct first {
	typedef typename T::first type;
};

template <typename T>
struct second {
	typedef typename T::second type;
};

}}}

#endif
