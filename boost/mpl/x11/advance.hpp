/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ADVANCE_APR_04_2013_1225)
#define MPL_X11_ADVANCE_APR_04_2013_1225

#include <boost/mpl/x11/detail/advance.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename Iterator, typename N>
struct advance
: detail::advance_impl<typename tag<Iterator>::type>
	::template apply<Iterator,N> {};

template <typename Iterator, long N>
struct advance_c
: detail::advance_impl<typename tag<Iterator>::type>
	::template apply<Iterator,long_<N>> {};

}}}

#endif
