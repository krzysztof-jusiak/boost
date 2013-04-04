/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_LAMBDA_APR_04_2013_1700)
#define MPL_X11_LAMBDA_APR_04_2013_1700

#include <boost/mpl/x11/void.hpp>
#include <boost/mpl/x11/detail/template_arity.hpp>

namespace boost { namespace mpl { namespace x11 {

template <
	typename T,
	typename Tag = void_,
	typename Arity = long_<detail::template_arity<T>::value>
> struct lambda {
	typedef std::false_type is_le;
	typedef T result_;
	typedef T type;
};

}}}

#endif
