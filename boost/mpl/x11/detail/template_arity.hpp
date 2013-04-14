/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_TEMPLATE_ARITY_APR_04_2013_1700)
#define MPL_X11_DETAIL_TEMPLATE_ARITY_APR_04_2013_1700

#include <boost/mpl/x11/integral.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename...>
struct template_arity;

template <typename T>
struct template_arity<T> : long_<0> {};

template <template <typename...> class F, typename... Tn>
struct template_arity<F<Tn...>> : long_<sizeof...(Tn)> {};

}}}}

#endif
