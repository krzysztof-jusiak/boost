/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ITERATOR_TAGS_APR_03_2013_1550)
#define MPL_X11_SEQUENCE_TAG_APR_03_2013_1550

#include <boost/mpl/x11/integral.hpp>

namespace boost { namespace mpl { namespace x11 {

struct forward_iterator_tag : int_<0> {
	typedef forward_iterator_tag type;
};

struct bidirectional_iterator_tag : int_<1> {
	typedef bidirectional_iterator_tag type;
};

struct random_access_iterator_tag : int_<2>
{
	typedef random_access_iterator_tag type;
};

}}}

#endif
