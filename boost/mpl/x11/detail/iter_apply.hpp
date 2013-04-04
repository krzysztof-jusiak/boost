/*=============================================================================
    Copyright (c) 2002-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_ITER_APPLY_APR_04_2013_1700)
#define MPL_X11_DETAIL_ITER_APPLY_APR_04_2013_1700

#include <boost/mpl/x11/apply.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename...>
struct iter_apply;

template <typename F, typename Iterator0>
struct iter_apply<F, Iterator0> : apply<F, typename deref<Iterator0>::type> {};

template <typename F, typename Iterator0, typename Iterator1>
struct iter_apply<F, Iterator0, Iterator1>
: apply<F, typename deref<Iterator0>::type, typename deref<Iterator0>::type> {};

}}}}

#endif
