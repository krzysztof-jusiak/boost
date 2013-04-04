/*=============================================================================
    Copyright (c) 2003-2004 Aleksey Gurtovoy
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_HAS_KEY_APR_04_2013_1325)
#define MPL_X11_DETAIL_HAS_KEY_APR_04_2013_1325

#include <boost/mpl/x11/sequence_tag_fwd.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename Tag>
struct has_key_impl {
	template <typename Sequence, typename Key>
	struct apply;
};

template <>
struct has_key_impl<non_sequence_tag> {};

}}}}

#endif
