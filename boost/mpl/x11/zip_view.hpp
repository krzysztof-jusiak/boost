/*=============================================================================
    Copyright (c) 2000-2010 Aleksey Gurtovoy
    Copyright (c) 2000-2002 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ZIP_VIEW_APR_18_2013_1645)
#define MPL_X11_ZIP_VIEW_APR_18_2013_1645

#include <boost/mpl/x11/iterator_tags.hpp>
#include <boost/mpl/x11/transform.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename IteratorSeq>
struct zip_iterator {
	typedef forward_iterator_tag category;
	typedef typename transform1<IteratorSeq, deref<arg<0>>>::type type;

	typedef zip_iterator<
		typename transform1<IteratorSeq, x11::next<arg<0>>>::type
	> next;
};

template <typename...>
struct zip_view;

template <>
struct zip_view<> {
	template <typename T0, typename... Tn>
	struct apply : zip_view<T0> {};
};

template <typename Tag>
struct lambda<zip_view<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef zip_view<> result_;
	typedef zip_view<> type;
};

template <typename Sequences>
struct zip_view<Sequences> {
	typedef typename transform1<
		Sequences, x11::begin<arg<0>>
	>::type first_ones_;
	typedef typename transform1<
		Sequences, x11::end<arg<0>>
	>::type last_ones_;

	typedef nested_begin_end_tag tag;
	typedef zip_view type;
	typedef zip_iterator<first_ones_> begin;
	typedef zip_iterator<last_ones_> end;
};

}}}

#endif
