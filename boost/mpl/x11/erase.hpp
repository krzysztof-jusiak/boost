/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ERASE_APR_04_2013_1225)
#define MPL_X11_ERASE_APR_04_2013_1225

#include <boost/mpl/x11/detail/erase.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename Sequence, typename First, typename Last>
struct erase
: detail::erase_impl<typename sequence_tag<Sequence>::type>
	::template apply<Sequence, First, Last> {};

template<typename Sequence, typename Key>
struct erase_key
: detail::erase_key_impl<typename sequence_tag<Sequence>::type>
	::template apply<Sequence,Key> {};

}}}

#endif
