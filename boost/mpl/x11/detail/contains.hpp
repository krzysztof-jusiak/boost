/*=============================================================================
    Copyright (c) 2002 Eric Friedman
    Copyright (c) 2004 Aleksey Gurtovoy
    Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_CONTAINS_APR_04_2013_1225)
#define MPL_X11_DETAIL_CONTAINS_APR_04_2013_1225

#include <boost/mpl/x11/sequence_tag_fwd.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/find.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename Tag>
struct contains_impl {
	template <typename Sequence, typename T>
	struct apply : not_<std::is_same<
		typename find<Sequence, T>::type,
		typename end<Sequence>::type
	>> {};
};

template <>
struct contains_impl<non_sequence_tag> {};

}}}}

#endif
