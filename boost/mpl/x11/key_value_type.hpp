/*=============================================================================
    Copyright (c) 2003-2004 Aleksey Gurtovoy
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_KEY_VALUE_TYPE_SEP_09_2013_1400)
#define MPL_X11_KEY_VALUE_TYPE_SEP_09_2013_1400

#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/lambda_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {

template <>
struct key_type<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : key_type<T0, T1> {};
};

template <typename Tag>
struct lambda<key_type<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef key_type<> result_;
	typedef key_type<> type;
};


template<typename Sequence, typename T>
struct key_type<Sequence, T> : apply_wrap<
	detail::key_type_impl<typename sequence_tag<Sequence>::type>,
	Sequence, T
> {};

template <>
struct value_type<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : value_type<T0, T1> {};
};

template <typename Tag>
struct lambda<value_type<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef value_type<> result_;
	typedef value_type<> type;
};

template<typename Sequence, typename T>
struct value_type<Sequence, T> : apply_wrap<
	detail::value_type_impl<typename sequence_tag<Sequence>::type>,
	Sequence, T
> {};

}}}

#endif
