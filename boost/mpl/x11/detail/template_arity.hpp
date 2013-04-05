/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_TEMPLATE_ARITY_APR_04_2013_1700)
#define MPL_X11_DETAIL_TEMPLATE_ARITY_APR_04_2013_1700

#include <boost/mpl/x11/detail/type_wrapper.hpp>
#include <boost/mpl/x11/arithmetic.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename...>
struct arity_helper;

template <typename F>
struct arity_helper<F> {
	typedef long_<0> type;
};

template <typename...>
struct arity_count;

template <typename T0>
struct arity_count<T0> {
	typedef long_<1> type;
};

template <typename T0, typename... Tn>
struct arity_count<T0, Tn...> {
	typedef increment<typename arity_count<Tn...>::type> type;
};

template <
	template <typename... Pn> class F,
	typename... Tn
> struct arity_helper<F<Tn...>> {
	typedef typename arity_count<Tn...>::type type;
};

template <typename F>
struct template_arity {
	typedef typename arity_helper<F>::type type;
	static int const value = type::value;
};

}}}}

#endif
