/*=============================================================================
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2004      Aleksey Gurtovoy    
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_PAIR_VIEW_APR_18_2013_1815)
#define MPL_X11_PAIR_VIEW_APR_18_2013_1815

#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/pair.hpp>
#include <boost/mpl/x11/deref.hpp>
#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/min_max.hpp>
#include <boost/mpl/x11/iterator_category.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct pair_iter_tag;

template <typename Iter0, typename Iter1, typename Category>
struct pair_iter {
    typedef pair_iter_tag tag;
    typedef Category category;
    typedef Iter0 first;
    typedef Iter1 second;
};

template <>
struct advance_impl<pair_iter_tag> {
	template <typename Iter, typename D>
	struct apply {
		typedef typename advance<typename Iter::first, D>::type i0_;
		typedef typename advance<typename Iter::second, D>::type i1_;
		typedef pair_iter<i0_, i1_, typename Iter::category> type;
	};
};

template <>
struct distance_impl<pair_iter_tag> {
	template <typename Iter0, typename Iter1>
	struct apply {
		typedef typename distance<
			typename first<Iter0>::type,
			typename first<Iter1>::type
		>::type type;
	};
};

}

template <typename Iter0, typename Iter1, typename C>
struct deref<detail::pair_iter<Iter0, Iter1, C>> {
	typedef pair<
		typename deref<Iter0>::type, typename deref<Iter1>::type
	> type;
};

template <typename Iter0, typename Iter1, typename C>
struct next<detail::pair_iter<Iter0, Iter1, C>> {
	typedef typename next<Iter0>::type i0_;
	typedef typename next<Iter1>::type i1_;
	typedef detail::pair_iter<i0_, i1_, C> type;
};

template <typename Iter0, typename Iter1, typename C>
struct prior<detail::pair_iter<Iter0, Iter1, C>> {
	typedef typename prior<Iter0>::type i0_;
	typedef typename prior<Iter1>::type i1_;
	typedef detail::pair_iter<i0_, i1_, C> type;
};

template <typename...>
struct pair_view;

template <>
struct pair_view<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : pair_view<T0, T1> {};
};

template <typename Tag>
struct lambda<pair_view<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef pair_view<> result_;
	typedef pair_view<> type;
};

template <typename Sequence0, typename Sequence1>
struct pair_view<Sequence0, Sequence1> {
	typedef nested_begin_end_tag tag;

	typedef typename begin<Sequence0>::type iter0_;
	typedef typename begin<Sequence1>::type iter1_;

	typedef typename min<
		typename iterator_category<iter0_>::type,
		typename iterator_category<iter1_>::type
	>::type category_;

	typedef detail::pair_iter<iter0_, iter1_, category_> begin;

	typedef detail::pair_iter<
		typename end<Sequence0>::type,
		typename end<Sequence1>::type,
		category_
	> end;
};

}}}

#endif
