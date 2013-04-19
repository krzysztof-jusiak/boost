/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_TRANSFORM_VIEW_APR_19_2013_1250)
#define MPL_X11_TRANSFORM_VIEW_APR_19_2013_1250

#include <boost/mpl/x11/lambda.hpp>
#include <boost/mpl/x11/apply.hpp>
#include <boost/mpl/x11/deref.hpp>
#include <boost/mpl/x11/begin_end.hpp>
#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/iterator_tags.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Iterator, typename LastIterator, typename F>
struct transform_iter {
	typedef Iterator base;
	typedef forward_iterator_tag category;
	typedef transform_iter<
		typename x11::next<base>::type, LastIterator, F
	> next;

	typedef typename apply<F, typename deref<base>::type>::type type;
};

template <typename LastIterator, typename F>
struct transform_iter<LastIterator, LastIterator, F> {
	typedef LastIterator base;
	typedef forward_iterator_tag category;
};

}

template <typename T0, typename T1, typename T2, typename Tag>
struct lambda<detail::transform_iter<T0, T1, T2>, Tag, long_<3>> {
	typedef false_type is_le;
	typedef detail::transform_iter<T0, T1, T2> result_;
	typedef result_ type;
};

template <typename...>
struct transform_view;

template <>
struct transform_view<> {
	template<typename T0, typename T1, typename... Tn>
	struct apply : transform_view<T0, T1> {};
};

template <typename Tag>
struct lambda<transform_view<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef transform_view<> result_;
	typedef transform_view<> type;
};

template <typename Sequence, typename F>
struct transform_view<Sequence, F> {
	typedef typename lambda<F>::type f_;
	typedef typename begin<Sequence>::type first_;
	typedef typename end<Sequence>::type last_;

	struct tag;
	typedef transform_view type;
	typedef detail::transform_iter<first_, last_, f_> begin;
	typedef detail::transform_iter<last_, last_, f_> end;
};

}}}

#endif
