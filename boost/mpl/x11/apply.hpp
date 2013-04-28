/*=============================================================================
    Copyright (c) 2000-2008 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_APPLY_APR_05_2013_1410)
#define MPL_X11_APPLY_APR_05_2013_1410

#include <boost/mpl/x11/lambda.hpp>
#include <boost/mpl/x11/apply_wrap.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct apply;

template <typename F>
struct apply<F> : apply_wrap<typename lambda<F>::type> {};

template <typename F, typename... Tn>
struct apply<F, Tn...> : apply_wrap<typename lambda<F>::type, Tn...> {};

}}}

#endif
