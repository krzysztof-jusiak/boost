/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_LOGICAL_MAR_31_2013_2300)
#define MPL_X11_LOGICAL_MAR_31_2013_2300

#include <boost/mpl/x11/integral.hpp>
#include <boost/mpl/x11/lambda_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename T>
struct nested_type_wknd : T::type {};

}

template <typename...>
struct or_;

template <>
struct or_<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : or_<T0, T1> {};
};

template <typename Tag>
struct lambda<or_<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef or_<> result_;
	typedef or_<> type;
};

template <typename T0>
struct or_<T0> : bool_<detail::nested_type_wknd<T0>::value> {};

template <typename T0, typename... Tn>
struct or_<T0, Tn...> : std::conditional<
	detail::nested_type_wknd<T0>::value, true_type, or_<Tn...>
>::type {};

template <typename...>
struct and_;

template <>
struct and_<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : and_<T0, T1> {};
};

template <typename Tag>
struct lambda<and_<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef and_<> result_;
	typedef and_<> type;
};

template <typename T0>
struct and_<T0> : bool_<detail::nested_type_wknd<T0>::value> {};

template <typename T0, typename... Tn>
struct and_<T0, Tn...> : std::conditional<
	detail::nested_type_wknd<T0>::value, and_<Tn...>, false_type
>::type {};

template <typename...>
struct not_;

template <>
struct not_<> {
	template <typename T0, typename... Tn>
	struct apply : not_<T0> {};
};

template <typename Tag>
struct lambda<not_<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef not_<> result_;
	typedef not_<> type;
};

template <typename T>
struct not_<T> : bool_<!detail::nested_type_wknd<T>::value> {};

}}}

#endif
