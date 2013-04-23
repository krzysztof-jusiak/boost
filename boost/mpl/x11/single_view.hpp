/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_SINGLE_VIEW_APR_23_2013_2300)
#define MPL_X11_SINGLE_VIEW_APR_23_2013_2300

#include <boost/mpl/x11/iterator_range.hpp>
#include <boost/mpl/x11/detail/single_element_iter.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct single_view;

template <>
struct single_view<> {
	template <typename T0, typename... Tn>
	struct apply : single_view<T0> {};
};

template <typename Tag>
struct lambda<single_view<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef single_view<> result_;
	typedef single_view<> type;
};

template <typename T>
struct single_view<T>
: iterator_range<detail::sel_iter<T, 0>, detail::sel_iter<T, 1>> {};

}}}

#endif
