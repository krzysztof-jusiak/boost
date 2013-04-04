/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_SAME_AS_APR_04_2013_1545)
#define MPL_X11_SAME_AS_APR_04_2013_1545

#include <boost/mpl/x11/logical.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename T>
struct same_as {
	template <typename U>
	struct apply : std::is_same<T, U> {};
};

template <typename T>
struct not_same_as {
	template <typename U>
	struct apply : not_<std::is_same<T, U>> {};
};


}}}

#endif
