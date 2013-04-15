/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DISTANCE_APR_15_2013_1640)
#define MPL_X11_DISTANCE_APR_15_2013_1640

#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/tag.hpp>
#include <boost/mpl/x11/iterator_range.hpp>
#include <boost/mpl/x11/iter_fold.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Tag>
struct distance_impl {
	template <typename First, typename Last>
	struct apply
	: iter_fold<iterator_range<First, Last>, long_<0>, next<>>::type {};
};

}

template <>
struct distance<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : distance<T0, T1> {};
};

template <typename Tag>
struct lambda<distance<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef distance<> result_;
	typedef distance<> type;
};

template <typename First, typename Last>
struct distance<First, Last>
: detail::distance_impl<typename tag<First>::type>
	::template apply<First, Last> {};


}}}

#endif
