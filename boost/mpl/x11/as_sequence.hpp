/*=============================================================================
    Copyright (c) 2002-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_AS_SEQUENCE_APR_23_2013_2300)
#define MPL_X11_AS_SEQUENCE_APR_23_2013_2300

#include <boost/mpl/x11/is_sequence.hpp>
#include <boost/mpl/x11/single_view.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct as_sequence;

template <>
struct as_sequence<> {
	template <typename T0, typename... Tn>
	struct apply : as_sequence<T0> {};
};

template <typename Tag>
struct lambda<as_sequence<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef as_sequence<> result_;
	typedef as_sequence<> type;
};

template <typename T>
struct as_sequence<T> : if_<is_sequence<T>, T, single_view<T>> {};

}}}

#endif
