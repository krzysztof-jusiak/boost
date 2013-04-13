/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ALWAYS_APR_05_2013_1325)
#define MPL_X11_ALWAYS_APR_05_2013_1325

#include <boost/mpl/x11/apply.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename Value>
struct always {
	template <typename... Tn>
	struct apply {
		typedef Value type;
	};
};

}}}

#endif
