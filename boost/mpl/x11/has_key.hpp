/*=============================================================================
    Copyright (c) 2003-2004 Aleksey Gurtovoy
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_HAS_KEY_APR_04_2013_1325)
#define MPL_X11_HAS_KEY_APR_04_2013_1325

#include <boost/mpl/x11/detail/has_key.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename Sequence, typename Key>
struct has_key
: detail::has_key_impl<typename sequence_tag<Sequence>::type>
	::template apply<Sequence, Key> {};

}}}

#endif
