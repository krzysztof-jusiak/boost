/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_ERASE_APR_04_2013_1225)
#define MPL_X11_DETAIL_ERASE_APR_04_2013_1225

#include <boost/mpl/x11/sequence_tag_fwd.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/iterator_range.hpp>
#include <boost/mpl/x11/reverse_fold.hpp>
#include <boost/mpl/x11/push_pop.hpp>
#include <boost/mpl/x11/clear.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename Tag>
struct erase_impl {
	template <
		typename Sequence, typename First,
		typename Last = typename next<First>::type
	> struct apply {
		typedef iterator_range<
			typename begin<Sequence>::type, First
		> first_half_;

		typedef iterator_range<
			Last, typename end<Sequence>::type
		> second_half_;

		typedef typename reverse_fold<
			second_half_,
			typename clear<Sequence>::type,
			push_front<arg<-1>, arg<-1>>
		>::type half_sequence_;

		typedef typename reverse_fold<
			first_half_, half_sequence_,
			push_front<arg<-1>, arg<-1>>
		>::type type;
	};
};

template <typename Tag>
struct erase_key_impl {
	template <typename Sequence, typename Key> struct apply;
};

template <>
struct erase_key_impl<non_sequence_tag> {};

}}}}

#endif
