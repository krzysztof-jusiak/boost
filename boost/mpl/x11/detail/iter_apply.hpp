/*=============================================================================
    Copyright (c) 2002-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_ITER_APPLY_APR_19_2013_1200)
#define MPL_X11_DETAIL_ITER_APPLY_APR_19_2013_1200

#include <boost/mpl/x11/deref.hpp>
#include <boost/mpl/x11/apply.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename F, typename... Iterator>
struct iter_apply : apply<F, typename deref<Iterator>::type...> {};

}}}}

#endif
