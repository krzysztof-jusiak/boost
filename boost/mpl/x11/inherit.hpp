/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_INHERIT_APR_25_2013_2300)
#define MPL_X11_INHERIT_APR_25_2013_2300

#include <boost/mpl/x11/lambda_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {

struct empty_base {};

template <typename T>
struct is_empty_base : false_type {};

template <>
struct is_empty_base<empty_base> : true_type {};

template <typename...>
struct inherit;

template <>
struct inherit<> {
	template <typename... Tn>
	struct apply : inherit<Tn...> {};
};

template <typename Tag>
struct lambda<inherit<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef inherit<> result_;
	typedef inherit<> type;
};

template <typename T0>
struct inherit<T0> : T0 {
	typedef T0 type;
};

template <typename T0, typename T1>
struct inherit<T0, T1> : T0, T1 {
	typedef inherit type;
};

template <typename T0>
struct inherit<T0, empty_base> : T0 {
	typedef T0 type;
};

template <typename T1>
struct inherit<empty_base, T1> : T1 {
	typedef T1 type;
};

template <>
struct inherit<empty_base, empty_base> {
	typedef empty_base type;
};

template <typename T0, typename T1, typename... Tn>
struct inherit<T0, T1, Tn...> : inherit<
	T0, typename inherit<T1, Tn...>::type
> {};

}}}

namespace std {

template <>
struct is_empty<boost::mpl::x11::empty_base> : std::true_type {};

}
#endif
