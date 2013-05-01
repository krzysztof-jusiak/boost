/*=============================================================================
    Copyright (c) 2002-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_IS_SEQUENCE_APR_19_2013_1200)
#define MPL_X11_IS_SEQUENCE_APR_19_2013_1200

#include <boost/mpl/x11/begin_end.hpp>
#include <boost/mpl/x11/logical.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct is_sequence;

template <>
struct is_sequence<> {
	template <typename T0, typename... Tn>
	struct apply : is_sequence<T0> {};
};

template <typename Tag>
struct lambda<is_sequence<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef is_sequence<> result_;
	typedef is_sequence<> type;
};

template <typename T>
struct is_sequence<T> : not_<std::is_same<typename begin<T>::type, void_>> {};

}}}

#endif
