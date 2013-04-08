/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ITERATOR_RANGE_APR_08_2013_1800)
#define MPL_X11_ITERATOR_RANGE_APR_08_2013_1800

namespace boost { namespace mpl { namespace x11 {

struct iterator_range_tag;

template <typename First, typename Last>
struct iterator_range {
	typedef iterator_range_tag tag;
	typedef iterator_range type;
	typedef First begin;
	typedef Last end;
};

}}}

#endif
