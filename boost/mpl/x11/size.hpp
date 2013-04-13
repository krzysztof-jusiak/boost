/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_SIZE_APR_02_2013_1745)
#define MPL_X11_SIZE_APR_02_2013_1745

#include <boost/mpl/x11/detail/size.hpp>

namespace boost { namespace mpl { namespace x11 {

template <>
struct size<> {
	template <typename T0, typename... Tn>
	struct apply : size<T0> {};
};

template <typename Sequence>
struct size<Sequence> : detail::size_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence>::type {};

template <typename Sequence>
struct empty : detail::empty_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence>::type {};

}}}

#endif
