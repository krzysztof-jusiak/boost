/*=============================================================================
    Copyright (c) 2004      Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_TAG_APR_15_2013_1730)
#define MPL_X11_TAG_APR_15_2013_1730

#include <boost/mpl/x11/detail/has_tag.hpp>
#include <boost/mpl/x11/if.hpp>
#include <boost/mpl/x11/void.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename T>
struct tag_impl {
	typedef typename T::tag type;
};

}

template <typename T, typename Default = void_>
struct tag : if_<detail::has_tag<T>, detail::tag_impl<T>, Default>::type {};

}}}

#endif
