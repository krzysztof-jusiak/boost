/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_CLEAR_APR_03_2013_2300)
#define MPL_X11_CLEAR_APR_03_2013_2300

#include <boost/mpl/x11/detail/clear.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename Sequence>
struct clear
: detail::clear_impl<typename sequence_tag<Sequence>::type>
	::template apply<Sequence>
{};

}}}

#endif
