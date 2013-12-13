/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_LAMBDA_APR_05_2013_1540)
#define MPL_X11_LAMBDA_APR_05_2013_1540

#include <boost/mpl/x11/lambda_fwd.hpp>
#include <boost/mpl/x11/if.hpp>
#include <boost/mpl/x11/quote.hpp>
#include <boost/mpl/x11/bind.hpp>
#include <boost/mpl/x11/identity.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <bool...>
struct lambda_or;

template <>
struct lambda_or<> {
	typedef false_type type;
};

template <bool C0, bool... Cn>
struct lambda_or<C0, Cn...> {
	typedef typename if_c<
		C0, true_type, typename lambda_or<Cn...>::type
	>::type type;
};


template <
	typename IsLE, typename Tag,
	template <typename...> class F, typename... Tn
> struct le_result {
	typedef F<typename Tn::type...> result_;

	typedef result_ type;
};

template <typename Tag, template <typename...> class F, typename... Tn>
struct le_result<true_type, Tag, F, Tn...> {
	typedef bind<quote<F, Tag>, typename Tn::result_...> result_;

	typedef protect<result_> type;
};

}

template <>
struct lambda<> {
	template <typename T0, typename T1, typename... Tn> struct apply
	: lambda<T0, T1> {};
};

template <typename Tag>
struct lambda<lambda<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef lambda<> result_;
	typedef lambda<> type;
};

template <typename T, typename Tag, typename Arity>
struct lambda<T, Tag, Arity> {
	typedef false_type is_le;
	typedef T result_;
	typedef T type;
};

template <typename T>
struct is_lambda_expression
: lambda<T>::is_le {};

template <long N, typename Tag>
struct lambda<arg<N>, Tag, long_<0>> {
	typedef true_type is_le;
	typedef arg<N> result_;
	typedef protect<result_> type;
};

template <typename F, typename Tag>
struct lambda<bind<F>, Tag, long_<1>> {
	typedef false_type is_le;
	typedef bind<F> result_;

	typedef result_ type;
};

template <template <typename... Pn> class F, typename T0, typename Tag>
struct lambda<F<T0>, Tag, long_<1>> {
	typedef lambda<T0, Tag> l0;
	typedef typename l0::is_le is_le0;
	typedef typename detail::lambda_or<is_le0::value>::type is_le;

	typedef detail::le_result<is_le, Tag, F, l0> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <typename T, typename Tag>
struct lambda<protect<T>, Tag, long_<1>> {
	typedef false_type is_le;
	typedef protect<T> result_;
	typedef result_ type;
};

template <typename F, typename T0, typename Tag>
struct lambda<bind<F, T0>, Tag, long_<2>> {
	typedef false_type is_le;
	typedef bind<F, T0> result_;

	typedef result_ type;
};

template <
	template <typename... Pn> class F, typename T0, typename T1,
	typename Tag
> struct lambda<F<T0, T1>, Tag, long_<2>> {
	typedef lambda<T0, Tag> l0;
	typedef lambda<T1, Tag> l1;

	typedef typename l0::is_le is_le0;
	typedef typename l1::is_le is_le1;

	typedef typename detail::lambda_or<
		is_le0::value, is_le1::value
	>::type is_le;

	typedef detail::le_result<is_le, Tag, F, l0, l1> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <typename F, typename T0, typename T1, typename Tag>
struct lambda<bind<F, T0, T1>, Tag, long_<3>> {
	typedef false_type is_le;
	typedef bind<F, T0, T1> result_;
	typedef result_ type;
};

template <
	template <typename... Pn> class F,
	typename T0, typename T1, typename T2, typename Tag
> struct lambda<F<T0, T1, T2>, Tag, long_<3>> {
	typedef lambda<T0, Tag> l0;
	typedef lambda<T1, Tag> l1;
	typedef lambda<T2, Tag> l2;

	typedef typename l0::is_le is_le0;
	typedef typename l1::is_le is_le1;
	typedef typename l2::is_le is_le2;

	typedef typename detail::lambda_or<
		is_le0::value, is_le1::value, is_le2::value
	>::type is_le;

	typedef detail::le_result<
		is_le, Tag, F, l0, l1, l2
	> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <typename F, typename Tag0, typename Tag1, typename Arity>
struct lambda<lambda<F, Tag0, Arity>, Tag1, long_<3>> {
	typedef lambda<F, Tag1> l0;
	typedef lambda<Tag0, Tag1> l1;
	typedef typename l0::is_le is_le;
	typedef bind<
		quote<detail::template_arity>, typename l0::result_
	> arity_;
	typedef lambda<typename if_<is_le, arity_, Arity>::type, Tag1> l2;
	typedef detail::le_result<
		is_le, Tag1, x11::lambda, l0, l1, l2
	> le_result_;
	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <
	typename F, typename T0, typename T1, typename T2, typename Tag
> struct lambda<bind<F, T0, T1, T2>, Tag, long_<4>> {
	typedef false_type is_le;
	typedef bind<F, T0, T1, T2> result_;

	typedef result_ type;
};

template <
	template <typename... Pn> class F,
	typename T0, typename T1, typename T2, typename T3, typename Tag
> struct lambda<F<T0, T1, T2, T3>, Tag, long_<4>> {
	typedef lambda<T0, Tag> l0;
	typedef lambda<T1, Tag> l1;
	typedef lambda<T2, Tag> l2;
	typedef lambda<T3, Tag> l3;

	typedef typename l0::is_le is_le0;
	typedef typename l1::is_le is_le1;
	typedef typename l2::is_le is_le2;
	typedef typename l3::is_le is_le3;

	typedef typename detail::lambda_or<
		is_le0::value, is_le1::value, is_le2::value, is_le3::value
	>::type is_le;

	typedef detail::le_result<
		is_le, Tag, F, l0, l1, l2, l3
	> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <
	typename F, typename T0, typename T1, typename T2, typename T3,
	typename Tag
> struct lambda<bind<F, T0, T1, T2, T3>, Tag, long_<5>> {
	typedef false_type is_le;
	typedef bind<F, T0, T1, T2, T3> result_;

	typedef result_ type;
};

template <
	template <typename... Pn> class F, typename T0, typename T1,
	typename T2, typename T3, typename T4, typename Tag
> struct lambda<F<T0, T1, T2, T3, T4>, Tag, long_<5>> {
	typedef lambda<T0, Tag> l0;
	typedef lambda<T1, Tag> l1;
	typedef lambda<T2, Tag> l2;
	typedef lambda<T3, Tag> l3;
	typedef lambda<T4, Tag> l4;

	typedef typename l0::is_le is_le0;
	typedef typename l1::is_le is_le1;
	typedef typename l2::is_le is_le2;
	typedef typename l3::is_le is_le3;
	typedef typename l4::is_le is_le4;


	typedef typename detail::lambda_or<
		is_le0::value, is_le1::value, is_le2::value, is_le3::value,
		is_le4::value
	>::type is_le;

	typedef detail::le_result<
		is_le, Tag, F, l0, l1, l2, l3, l4
	> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <
	typename F, typename T0, typename T1, typename T2, typename T3,
	typename T4, typename Tag
> struct lambda<bind<F, T0, T1, T2, T3, T4>, Tag, long_<6>> {
	typedef false_type is_le;
	typedef bind<F, T0, T1, T2, T3, T4> result_;

	typedef result_ type;
};

}}}

#endif
