/*=============================================================================
    Copyright (c) 2000-2008 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_QUOTE_APR_06_2013_2300)
#define MPL_X11_QUOTE_APR_06_2013_2300

#include <boost/mpl/x11/detail/has_type.hpp>
#include <boost/mpl/x11/void.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename T, bool has_type_>
struct quote_impl {
	typedef typename T::type type;
};

template <typename T>
struct quote_impl<T, false> {
    typedef T type;
};

}

template <template <typename... Pn> class F, typename Tag = void_>
struct quote {
	template <typename... Un>
	struct apply
	: detail::quote_impl<F<Un...>, detail::has_type<F<Un...>>::value>
	{};
};

}}}

#endif
