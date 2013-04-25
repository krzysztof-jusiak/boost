/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_INSERT_APR_04_2013_1425)
#define MPL_X11_DETAIL_INSERT_APR_04_2013_1425

#include <boost/mpl/x11/reverse_fold.hpp>
#include <boost/mpl/x11/joint_view.hpp>
#include <boost/mpl/x11/push_pop.hpp>
#include <boost/mpl/x11/clear.hpp>
#include <boost/mpl/x11/copy.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename Tag>
struct insert_impl {
	template <typename Sequence, typename Pos, typename T = Pos>
	struct apply {
		typedef iterator_range<
			typename begin<Sequence>::type, Pos
		> first_half_;

		typedef iterator_range<
			Pos, typename end<Sequence>::type
		> second_half_;

		typedef typename reverse_fold<
			second_half_,
			typename clear<Sequence>::type,
			push_front<arg<-1>, arg<-1>>
		>::type half_sequence_;

		typedef typename reverse_fold<
			first_half_,
			typename push_front<half_sequence_, T>::type,
			push_front<arg<-1>, arg<-1>>
		>::type type;
	};
};

template <>
struct insert_impl<non_sequence_tag> {};

template <typename Tag>
struct insert_range_impl {
	template <typename Sequence, typename Pos, typename Range>
	struct apply : reverse_copy<
		joint_view<
			iterator_range<typename begin<Sequence>::type, Pos>,
			joint_view<
				Range,
				iterator_range<
					Pos, typename end<Sequence>::type
				>
			>
		>, front_inserter<typename clear<Sequence>::type>
	> {};
};

template <>
struct insert_range_impl<non_sequence_tag> {};

}}}}

#endif
