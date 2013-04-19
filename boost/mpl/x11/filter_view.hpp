/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_FILTER_VIEW_APR_19_2013_1330)
#define MPL_X11_FILTER_VIEW_APR_19_2013_1330

#include <boost/mpl/x11/lambda.hpp>
#include <boost/mpl/x11/find.hpp>


namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Iterator, typename LastIterator, typename Predicate>
struct filter_iter;

template <typename Iterator, typename LastIterator, typename Predicate>
struct next_filter_iter {
	typedef typename find_if<
		iterator_range<Iterator, LastIterator>, Predicate
	>::type base_iter_;

	typedef filter_iter<base_iter_, LastIterator, Predicate> type;
};

template <typename Iterator, typename LastIterator, typename Predicate>
struct filter_iter {
	typedef Iterator base;
	typedef forward_iterator_tag category;
	typedef typename next_filter_iter<
		typename x11::next<base>::type, LastIterator, Predicate
	>::type next;

	typedef typename deref<base>::type type;
};

template <typename LastIterator, typename Predicate>
struct filter_iter <LastIterator, LastIterator, Predicate> {
	typedef LastIterator base;
	typedef forward_iterator_tag category;
};

}

template <typename T0, typename T1, typename T2, typename Tag>
struct lambda<detail::filter_iter<T0, T1, T2>, Tag, long_<3>> {
	typedef false_type is_le;
	typedef detail::filter_iter<T0, T1, T2> result_;
	typedef result_ type;
};

template <typename...>
struct filter_view;

template <>
struct filter_view<> {
	template<typename T0, typename T1, typename... Tn>
	struct apply : filter_view<T0, T1> {};
};

template <typename Tag>
struct lambda<filter_view<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef filter_view<> result_;
	typedef filter_view<> type;
};

template <typename Sequence, typename Predicate>
struct filter_view<Sequence, Predicate> {
	typedef typename lambda<Predicate>::type pred_;
	typedef typename begin<Sequence>::type first_;
	typedef typename end<Sequence>::type last_;

	struct tag;
	typedef filter_view type;
	typedef typename detail::next_filter_iter<
		first_, last_, pred_
	>::type begin;
	typedef detail::filter_iter<last_, last_, pred_> end;
};

}}}

#endif
