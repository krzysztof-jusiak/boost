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
	typedef detail::replace_unnamed_arg<F, arg<0>> r0;

	template <typename... Un>
	struct apply {
		typedef typename detail::resolve_bind_arg<
			typename r0::type, Un...
		>::type f_;

		typedef typename apply_wrap<f_>::type type;
	};

};

template <typename F, typename T0>
struct bind<F, T0> {
	typedef detail::replace_unnamed_arg<F, arg<0>> r0;
	typedef detail::replace_unnamed_arg<T0, typename r0::next> r1;

	template <typename... Un>
	struct apply {
		typedef typename detail::resolve_bind_arg<
			typename r0::type, Un...
		>::type f_;

		typedef typename detail::resolve_bind_arg<
			typename r1::type, Un...
		>::type t0;

		typedef typename apply_wrap<f_, t0>::type type;
	};
};

template <typename F, typename T0, typename T1>
struct bind<F, T0, T1> {
	typedef detail::replace_unnamed_arg<F, arg<0>> r0;
	typedef detail::replace_unnamed_arg<T0, typename r0::next> r1;
	typedef detail::replace_unnamed_arg<T1, typename r1::next> r2;

	template <typename... Un>
	struct apply {
		typedef typename detail::resolve_bind_arg<
			typename r0::type, Un...
		>::type f_;

		typedef typename detail::resolve_bind_arg<
			typename r1::type, Un...
		>::type t0;

		typedef typename detail::resolve_bind_arg<
			typename r2::type, Un...
		>::type t1;

		typedef typename apply_wrap<f_, t0, t1>::type type;
	};
};

template <typename F, typename T0, typename T1, typename T2>
struct bind<F, T0, T1, T2> {
	typedef detail::replace_unnamed_arg<F, arg<0>> r0;
	typedef detail::replace_unnamed_arg<T0, typename r0::next> r1;
	typedef detail::replace_unnamed_arg<T1, typename r1::next> r2;
	typedef detail::replace_unnamed_arg<T2, typename r2::next> r3;

	template <typename... Un>
	struct apply {
		typedef typename detail::resolve_bind_arg<
			typename r0::type, Un...
		>::type f_;

		typedef typename detail::resolve_bind_arg<
			typename r1::type, Un...
		>::type t0;

		typedef typename detail::resolve_bind_arg<
			typename r2::type, Un...
		>::type t1;

		typedef typename detail::resolve_bind_arg<
			typename r3::type, Un...
		>::type t2;

		typedef typename apply_wrap<f_, t0, t1, t2>::type type;
	};
};

template <typename F, typename T0, typename T1, typename T2, typename T3>
struct bind<F, T0, T1, T2, T3> {
	typedef detail::replace_unnamed_arg<F, arg<0>> r0;
	typedef detail::replace_unnamed_arg<T0, typename r0::next> r1;
	typedef detail::replace_unnamed_arg<T1, typename r1::next> r2;
	typedef detail::replace_unnamed_arg<T2, typename r2::next> r3;
	typedef detail::replace_unnamed_arg<T3, typename r3::next> r4;

	template <typename... Un>
	struct apply {
		typedef typename detail::resolve_bind_arg<
			typename r0::type, Un...
		>::type f_;

		typedef typename detail::resolve_bind_arg<
			typename r1::type, Un...
		>::type t0;

		typedef typename detail::resolve_bind_arg<
			typename r2::type, Un...
		>::type t1;

		typedef typename detail::resolve_bind_arg<
			typename r3::type, Un...
		>::type t2;

		typedef typename detail::resolve_bind_arg<
			typename r4::type, Un...
		>::type t3;

		typedef typename apply_wrap<f_, t0, t1, t2, t3>::type type;
	};
};

template <
	typename F, typename T0, typename T1, typename T2, typename T3,
	typename T4
> struct bind<F, T0, T1, T2, T3, T4> {
	typedef detail::replace_unnamed_arg<F, arg<0>> r0;
	typedef detail::replace_unnamed_arg<T0, typename r0::next> r1;
	typedef detail::replace_unnamed_arg<T1, typename r1::next> r2;
	typedef detail::replace_unnamed_arg<T2, typename r2::next> r3;
	typedef detail::replace_unnamed_arg<T3, typename r3::next> r4;
	typedef detail::replace_unnamed_arg<T4, typename r4::next> r5;

	template <typename... Un>
	struct apply {
		typedef typename detail::resolve_bind_arg<
			typename r0::type, Un...
		>::type f_;

		typedef typename detail::resolve_bind_arg<
			typename r1::type, Un...
		>::type t0;

		typedef typename detail::resolve_bind_arg<
			typename r2::type, Un...
		>::type t1;

		typedef typename detail::resolve_bind_arg<
			typename r3::type, Un...
		>::type t2;

		typedef typename detail::resolve_bind_arg<
			typename r4::type, Un...
		>::type t3;

		typedef typename detail::resolve_bind_arg<
			typename r5::type, Un...
		>::type t4;

		typedef typename apply_wrap<f_, t0, t1, t2, t3, t4>::type type;
	};
};

template <template <typename... Pn> class F, typename Tag> struct quote;

template <typename Tc, typename T0, typename T1> struct if_;

template <typename Tc, typename T0, typename T1> struct eval_if;

template <typename Tag, typename T0, typename T1, typename T2>
struct bind<quote<if_, Tag>, T0, T1, T2> {
	typedef arg<0> r0;
	typedef detail::replace_unnamed_arg<T0, typename r0::next> r1;
	typedef detail::replace_unnamed_arg<T1, typename r1::next> r2;
	typedef detail::replace_unnamed_arg<T2, typename r2::next> r3;

	template <typename... Un>
	struct apply {
		typedef typename detail::resolve_bind_arg<
			typename r1::type, Un...
		> t0;

		typedef typename detail::resolve_bind_arg<
			typename r2::type, Un...
		> t1;

		typedef typename detail::resolve_bind_arg<
			typename r3::type, Un...
		> t2;

		typedef typename if_<typename t0::type, t1, t2>::type f_;

		typedef typename f_::type type;
	};
};

template <typename Tag, typename T0, typename T1, typename T2>
struct bind<quote<eval_if, Tag>, T0, T1, T2> {
	typedef arg<0> r0;
	typedef detail::replace_unnamed_arg<T0, typename r0::next> r1;
	typedef detail::replace_unnamed_arg<T1, typename r1::next> r2;
	typedef detail::replace_unnamed_arg<T2, typename r2::next> r3;

	template <typename... Un>
	struct apply {
		typedef typename detail::resolve_bind_arg<
			typename r1::type, Un...
		> t0;

		typedef typename detail::resolve_bind_arg<
			typename r2::type, Un...
		> t1;

		typedef typename detail::resolve_bind_arg<
			typename r3::type, Un...
		> t2;

		typedef typename eval_if<typename t0::type, t1, t2>::type f_;

		typedef typename f_::type type;
	};
};

}}}

#endif
