/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2001      Peter Dimov
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_BIND_APR_05_2013_1600)
#define MPL_X11_BIND_APR_05_2013_1600

#include <boost/mpl/x11/arg.hpp>
#include <boost/mpl/x11/apply_wrap.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct bind;

namespace detail {

template <typename T, typename Arg>
struct replace_unnamed_arg {
	typedef Arg next;
	typedef T type;
};

template <typename Arg>
struct replace_unnamed_arg<arg<-1>, Arg> {
	typedef typename Arg::next next;
	typedef Arg type;
};

template <typename...>
struct resolve_bind_arg;

template <typename T, typename... Un>
struct resolve_bind_arg<T, Un...> {
	typedef T type;
};

template <typename F, typename... Tn, typename... Un>
struct resolve_bind_arg<bind<F, Tn...>, Un...> {
	typedef bind<F, Tn...> f_;
	typedef typename apply_wrap<f_, Un...>::type type;
};

template <long N, typename... Un>
struct resolve_bind_arg<arg<N>, Un...> {
	typedef typename apply_wrap<arg<N>, Un...>::type type;
};

}

template <typename F>
struct bind<F> {
	template <typename... Un>
	struct apply {
		typedef detail::replace_unnamed_arg<F, arg<0>> r0;
		typedef typename r0::type a0;
		typedef typename r0::next n1;
		typedef typename detail::resolve_bind_arg<a0, Un...>::type f_;

		typedef typename apply_wrap<f_>::type type;
	};

};

template <typename F, typename T0>
struct bind<F, T0> {
	template <typename... Un>
	struct apply {
		typedef detail::replace_unnamed_arg<F, mpl::arg<0>> r0;
		typedef typename r0::type a0;
		typedef typename r0::next n1;
		typedef typename detail::resolve_bind_arg<a0, Un...>::type f_;

		typedef detail::replace_unnamed_arg<T0, n1> r1;
		typedef typename r1::type a1;
		typedef typename r1::next n2;
		typedef detail::resolve_bind_arg<a1, Un...> t1;

		typedef typename apply_wrap<f_, typename t1::type>::type type;
	};
};

template <typename F, typename T0, typename T1>
struct bind<F, T0, T1> {
	template <typename... Un>
	struct apply {
		typedef detail::replace_unnamed_arg<F, arg<0>> r0;
		typedef typename r0::type a0;
		typedef typename r0::next n1;
		typedef typename detail::resolve_bind_arg<a0, Un...>::type f_;

		typedef detail::replace_unnamed_arg<T0, n1> r1;
		typedef typename r1::type a1;
		typedef typename r1::next n2;
		typedef detail::resolve_bind_arg<a1, Un...> t1;

		typedef detail::replace_unnamed_arg<T1, n2> r2;
		typedef typename r2::type a2;
		typedef typename r2::next n3;
		typedef detail::resolve_bind_arg<a2, Un...> t2;

		typedef typename apply_wrap<
			f_, typename t1::type, typename t2::type
		>::type type;
	};
};

}}}

#endif
