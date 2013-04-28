/*=============================================================================
    Copyright (c) 2000-2008 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_MIN_MAX_APR_19_2013_1130)
#define MPL_X11_MIN_MAX_APR_19_2013_1130

#include <boost/mpl/x11/comparison.hpp>
#include <boost/mpl/x11/if.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct min;

template <>
struct min<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : min<T0, T1> {};
};

template <typename Tag>
struct lambda<min<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef min<> result_;
	typedef min<> type;
};

template <typename N0, typename N1>
struct min<N0, N1> : if_<less<N0, N1>, N0, N1> {};

template <typename...>
struct max;

template <>
struct max<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : max<T0, T1> {};
};

template <typename Tag>
struct lambda<max<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef max<> result_;
	typedef max<> type;
};

template <typename N0, typename N1>
struct max<N0, N1> : if_<less<N0, N1>, N1, N0> {};

}}}

#endif
