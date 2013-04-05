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
#include <boost/mpl/x11/arg.hpp>

namespace boost { namespace mpl { namespace x11 {

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
struct lambda<arg<N>, Tag, int_< -1 >> {
	typedef std::true_type is_le;
	typedef arg<N> result_;
	typedef protect<result_> type;
};
/*
template <typename F, typename Tag>
struct lambda<bind0<F>, Tag, int_<1>> {
	typedef std::false_type is_le;
	typedef bind0<F> result_;

	typedef result_ type;
};
*/

namespace detail {

template <
	typename IsLE, typename Tag,
	template <typename P1> class F, typename L1
> struct le_result1 {
	typedef F<typename L1::type> result_;

	typedef result_ type;
};
/*
template <typename Tag, template <typename P1> class F, typename L1>
struct le_result1<std::true_type, Tag, F, L1> {
	typedef bind1<quote1<F, Tag>, typename L1::result_> result_;

	typedef protect<result_> type;
};
*/
}

template <template <typename P1> class F, typename T1, typename Tag>
struct lambda<F<T1>, Tag, int_<1>> {
	typedef lambda<T1, Tag > l1;
	typedef typename l1::is_le is_le1;
	typedef typename detail::lambda_or<is_le1::value>::type is_le;

	typedef detail::le_result1<is_le, Tag, F, l1> le_result_;

	typedef typename le_result_::result_ result_;
	typedef typename le_result_::type type;
};
/*
template <typename F, typename T1, typename Tag>
struct lambda<bind1< F,T1 >, Tag, int_<2>> {
	typedef false_ is_le;
	typedef bind1<F, T1> result_;

	typedef result_ type;
};
*/


}}}

#endif
