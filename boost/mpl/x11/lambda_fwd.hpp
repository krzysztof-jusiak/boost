/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_LAMBDA_FWD_APR_04_2013_1700)
#define MPL_X11_LAMBDA_FWD_APR_04_2013_1700

#include <boost/mpl/x11/void.hpp>
#include <boost/mpl/x11/detail/template_arity.hpp>

namespace boost { namespace mpl { namespace x11 {
/*
template <typename...>
struct lambda;

template <typename T, typename Tag, typename Arity>
struct lambda<T, Tag, Arity>;

template <typename T, typename Tag>
struct lambda<T, Tag>
: lambda<T, Tag, typename detail::template_arity<T>::type> {};

template <typename T>
struct lambda<T> : lambda<T, void_> {};
*/

template <
	typename T,
	typename Tag = void_,
	typename Arity = typename detail::template_arity<T>::type
> struct lambda;

}}}

#endif
