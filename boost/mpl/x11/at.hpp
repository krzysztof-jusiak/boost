/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_AT_APR_04_2013_1225)
#define MPL_X11_AT_APR_04_2013_1225

#include <boost/mpl/x11/detail/at.hpp>
#include <boost/mpl/x11/integral.hpp>

namespace boost { namespace mpl { namespace x11 {

template <>
struct at<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : at<T0, T1> {};
};

template <typename Sequence, typename N>
struct at<Sequence, N>
: detail::at_impl<typename sequence_tag<Sequence>::type>
	::template apply<Sequence, N> {};

template<typename Sequence, long N>
struct at_c
: detail::at_impl<typename sequence_tag<Sequence>::type>
	::template apply<Sequence, long_<N>> {};

}}}

#endif
