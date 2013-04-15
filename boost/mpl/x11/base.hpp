/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_BASE_APR_10_2013_1830)
#define MPL_X11_BASE_APR_10_2013_1830

#include <boost/mpl/x11/lambda_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct base;

template <>
struct base<> {
	template <typename T0, typename... Tn>
	struct apply : base<T0> {};
};

template <typename Tag>
struct lambda<base<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef base<> result_;
	typedef base<> type;
};

template <typename T>
struct base<T> {
	typedef typename T::base type;
};




}}}

#endif
