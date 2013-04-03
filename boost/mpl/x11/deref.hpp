/*=============================================================================
    Copyright (c) 2002-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DEREF_APR_03_2013_1300)
#define MPL_X11_DEREF_APR_03_2013_1300

namespace boost { namespace mpl { namespace x11 {

template <typename Iterator>
struct deref {
	typedef typename Iterator::type type;
};

}}}

#endif
