/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_SIZE_APR_02_2013_1745)
#define MPL_X11_DETAIL_SIZE_APR_02_2013_1745

#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/sequence_tag.hpp>
#include <boost/mpl/x11/distance.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename Tag>
struct size_impl {
	template <typename Sequence>
	struct apply : distance<
		typename begin<Sequence>::type,
		typename end<Sequence>::type
	> {};
};

template <>
struct size_impl<non_sequence_tag> {};

template <typename Tag>
struct empty_impl {
	template <typename Sequence>
	struct apply : std::is_same<
		typename begin<Sequence>::type,
		typename end<Sequence>::type
	> {};
};

template <>
struct empty_impl<non_sequence_tag> {};

}}}}

#endif
