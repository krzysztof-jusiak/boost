/*=============================================================================
    Copyright (c) 2002-2008 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_PUSH_POP_APR_03_2013_1400)
#define MPL_X11_DETAIL_PUSH_POP_APR_03_2013_1400

#include <boost/mpl/x11/sequence_tag_fwd.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/detail/has_type.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

struct has_push_back_arg {};
struct has_push_front_arg {};

template <typename Tag>
struct pop_back_impl {
	template <typename Sequence>
	struct apply;
};

template <>
struct pop_back_impl<non_sequence_tag> {};

template <typename Tag>
struct pop_front_impl {
	template <typename Sequence>
	struct apply;
};

template <>
struct pop_front_impl<non_sequence_tag> {};

template <typename Tag>
struct push_back_impl {
	template <typename Sequence, typename T>
	struct apply {};
};

template <typename Tag>
struct has_push_back_impl {
	template <typename Sequence>
	struct apply : has_type<push_back<Sequence, has_push_back_arg>> {};
};

template <typename Tag>
struct push_front_impl {
	template <typename Sequence, typename T>
	struct apply {};
};

template <typename Tag>
struct has_push_front_impl {
	template <typename Sequence>
	struct apply : has_type<push_front<Sequence, has_push_front_arg>> {};
};

template <>
struct has_push_back_impl<non_sequence_tag> {};

template <>
struct has_push_front_impl<non_sequence_tag> {};

}}}}

#endif
