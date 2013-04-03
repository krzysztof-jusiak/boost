/*=============================================================================
    Copyright (c) 2003-2004 Aleksey Gurtovoy
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_ORDER_APR_03_2013_2300)
#define MPL_X11_DETAIL_ORDER_APR_03_2013_2300

#include <boost/mpl/x11/sequence_tag_fwd.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename Sequence, typename Key>
struct x_order_impl : long_<
	sizeof(
		Sequence::order_by_key_(
			ptr_to_ref(static_cast<Sequence *>(nullptr)),
			static_cast<type_wrapper<Key> *>(nullptr)
		)
	)
> {};

template <typename Tag>
struct order_impl {
	template <typename Sequence, typename Key>
	struct apply : if_<
		typename has_key_impl<Tag>::template apply<Sequence, Key>,
		x_order_impl<Sequence, Key>, void_
	>::type {};
};

template <>
struct order_impl<non_sequence_tag> {};

}}}}

#endif
