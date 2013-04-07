/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_LAMBDA_APR_05_2013_1540)
#define MPL_X11_LAMBDA_APR_05_2013_1540

#include <boost/mpl/x11/lambda_fwd.hpp>
#include <boost/mpl/x11/integral.hpp>
#include <boost/mpl/x11/quote.hpp>
#include <boost/mpl/x11/bind.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <bool...>
struct lambda_or;

template <bool C0>
struct lambda_or {
	typedef typename bool_<C0>::type type;
};

template <bool C0, bool... Cn>
struct lambda_or<C0, Cn...> {
	typedef typename if_c<C0, std::true_type, lambda_or<Cn...>::type type;
};

template <
	typename IsLE, typename Tag,
	template <typename P0> class F, typename L0
> struct le_result1 {
	typedef F<typename L0::type> result_;

	typedef result_ type;
};

template <typename Tag, template <typename P0> class F, typename L0>
struct le_result1<std::true_type, Tag, F, L0> {
	typedef bind<quote<F, Tag>, typename L0::result_> result_;

	typedef protect<result_> type;
};

template <
	typename IsLE, typename Tag,
	template <typename P0, typename P1> class F, typename L0, typename L1
> struct le_result2 {
	typedef F<typename L0::type, typename L1::type> result_;

	typedef result_ type;
};

template <
	typename Tag, template <typename P0, typename P1> class F,
	typename L0, typename L1
> struct le_result2<std::true_type, Tag, F, L0, L1> {
	typedef bind<
		quote<F, Tag>, typename L0::result_, typename L1::result_
	> result_;

	typedef protect<result_> type;
};

template <
	typename IsLE, typename Tag,
	template <typename P0, typename P1, typename P2> class F,
	typename L0, typename L1, typename L2
> struct le_result3 {
	typedef F<
		typename L0::type, typename L1::type, typename L2::type
	> result_;

	typedef result_ type;
};

template <
	typename Tag, template <typename P0, typename P1, typename P2> class F,
	typename L0, typename L1, typename L2
> struct le_result3<std::true_type, Tag, F, L0, L1, L2> {
	typedef bind<
		quote<F, Tag>, typename L0::result_, typename L1::result_,
		typename L2::result_
        > result_;

	typedef protect<result_> type;
};

template <
	typename IsLE, typename Tag,
	template <typename P0, typename P1, typename P2, typename P3> class F,
	typename L0, typename L1, typename L2, typename L3
> struct le_result4 {
	typedef F<
		typename L0::type, typename L1::type, typename L2::type,
		typename L3::type
	> result_;

	typedef result_ type;
};

template <
	typename Tag,
	template <typename P0, typename P1, typename P2, typename P3> class F,
	typename L0, typename L1, typename L2, typename L3
> struct le_result4<std::true_type, Tag, F, L0, L1, L2, L3> {
	typedef bind<
		quote<F, Tag>, typename L0::result_, typename L1::result_,
		typename L2::result_, typename L3::result_
        > result_;

	typedef protect<result_> type;
};

template <
	typename IsLE, typename Tag,
	template <
		typename P0, typename P1, typename P2, typename P3, typename P4
	> class F, typename L0, typename L1, typename L2, typename L3,
	typename L4
> struct le_result5 {
	typedef F<
		typename L0::type, typename L1::type, typename L2::type,
		typename L3::type, typename L4::type
	> result_;

	typedef result_ type;
};

template <
	typename Tag, template <
		typename P0, typename P1, typename P2, typename P3, typename P4
	> class F, typename L0, typename L1, typename L2, typename L3,
	typename L4
> struct le_result5<std::true_type, Tag, F, L0, L1, L2, L3, L4> {
	typedef bind<
		quote<F, Tag>, typename L0::result_, typename L1::result_,
		typename L2::result_, typename L3::result_, typename L4::result_
	> result_;

	typedef protect<result_> type;
};

}

template <typename T, typename Tag, typename Arity>
struct lambda {
	typedef std::false_type is_le;
	typedef T result_;
	typedef T type;
};

template <typename T>
struct is_lambda_expression
: lambda<T>::is_le {};

template <int N, typename Tag>
struct lambda<arg<N>, Tag, long_< -1 >> {
	typedef std::true_type is_le;
	typedef arg<N> result_;
	typedef protect<result_> type;
};

template <typename F, typename Tag>
struct lambda<bind<F>, Tag, long_<1>> {
	typedef std::false_type is_le;
	typedef bind<F> result_;

	typedef result_ type;
};

template <template <typename P0> class F, typename T0, typename Tag>
struct lambda<F<T0>, Tag, long_<1>> {
	typedef lambda<T0, Tag> l0;
	typedef typename l0::is_le is_le0;
	typedef typename detail::lambda_or<is_le0::value>::type is_le;

	typedef detail::le_result1<is_le, Tag, F, l0> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <typename T, typename Tag>
struct lambda<protect<T>, Tag, long_<1>> {
	typedef std::false_type is_le;
	typedef protect<T> result_;
	typedef result_ type;
};

template <typename F, typename T0, typename Tag>
struct lambda<bind<F, T0>, Tag, long_<2>> {
	typedef std::false_type is_le;
	typedef bind<F, T0> result_;

	typedef result_ type;
};

template <
	template <typename P0, typename P1> class F, typename T0, typename T1,
	typename Tag
> struct lambda<F<T0, T1>, Tag, long_<2>> {
	typedef lambda<T0, Tag> l0;
	typedef lambda<T1, Tag> l1;

	typedef typename l0::is_le is_le0;
	typedef typename l1::is_le is_le1;

	typedef typename detail::lambda_or<
		is_le0::value, is_le1::value
	>::type is_le;

	typedef detail::le_result2<is_le, Tag, F, l0, l1> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <typename F, typename T0, typename T1, typename Tag>
struct lambda<bind<F, T0, T1>, Tag, long_<3>> {
	typedef std::false_type is_le;
	typedef bind<F, T0, T1> result_;
	typedef result_ type;
};

template <
	template <typename P0, typename P1, typename P2> class F,
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

	typedef detail::le_result3<
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
	typedef le_result3<is_le, Tag2, lambda, l0, l1, l2> le_result_;
	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <
	typename F, typename T0, typename T1, typename T2, typename Tag
> struct lambda<bind<F, T0, T1, T2>, Tag, long_<4>> {
	typedef std::false_type is_le;
	typedef bind<F, T0, T1, T2> result_;

	typedef result_ type;
};

template <
	template <typename P0, typename P1, typename P2, typename P3 > class F,
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

	typedef detail::le_result4<
		is_le, Tag, F, l0, l1, l2, l3
	> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <
	typename F, typename T0, typename T1, typename T2, typename T3,
	typename Tag
> struct lambda<bind<F, T0, T1, T2, T3>, Tag, long_<5>> {
	typedef std::false_type is_le;
	typedef bind<F, T0, T1, T2, T3> result_;

	typedef result_ type;
};

template <
	template <
		typename P0, typename P1, typename P2, typename P3, typename P4
	> class F, typename T0, typename T1, typename T2, typename T3,
	typename T4, typename Tag
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

	typedef detail::le_result5<
		is_le, Tag, F, l0, l1, l2, l3, l4
	> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};

template <
	typename F, typename T0, typename T1, typename T2, typename T3,
	typename T4, typename Tag
> struct lambda<bind<F, T0, T1, T2, T3, T4>, Tag, long_<6>> {
	typedef std::false_type is_le;
	typedef bind<F, T0, T1, T2, T3, T4> result_;

	typedef result_ type;
};

template <
	typename F, typename T0, typename T1, typename T2, typename T3,
	typename T4, typename Tag
> struct lambda<bind<F, T0, T1, T2, T3, T4>, Tag, long_<6>> {
	typedef std::false_type is_le;
	typedef bind<F, T0, T1, T2, T3, T4> result_;
	typedef result_ type;
};

}}}

#endif
