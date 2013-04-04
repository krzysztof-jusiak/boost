/*=============================================================================
    Copyright (c) 2000-2008 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_APPLY_APR_04_2013_1410)
#define MPL_X11_APPLY_APR_04_2013_1410

#include <boost/mpl/x11/lambda.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct apply_wrap;

template <typename F>
struct apply_wrap<F> : F::template apply<> {};

template <typename F, typename T0>
struct apply_wrap<F, T0> : F::template apply<T0> {};

template <typename F, typename T0, typename... Tn>
struct apply_wrap<F, T0, Tn...> : F::template apply<T0, Tn...> {};

template <typename...>
struct apply;

template <typename F>
struct apply<F> : apply_wrap<typename lambda<F>::type> {};

template <typename F, typename T0>
struct apply<F, T0> : apply_wrap<typename lambda<F>::type, T0> {};

template <typename F, typename T0, typename... Tn>
struct apply<F, T0, Tn...>
: apply_wrap<typename lambda<F>::type, T0, Tn...> {};

}}}

#endif
