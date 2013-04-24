/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DEQUE_APR_24_2013_2300)
#define MPL_X11_DEQUE_APR_24_2013_2300

#include <boost/mpl/x11/vector.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename... Tn>
struct deque : vector<Tn...> {
	typedef typename vector<Tn...>::type type;
};

}}}

#endif
