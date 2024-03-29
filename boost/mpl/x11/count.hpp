/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_COUNT_APR_24_2013_2300)
#define MPL_X11_COUNT_APR_24_2013_2300

#include <boost/mpl/x11/fold.hpp>
#include <boost/mpl/x11/same_as.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Predicate>
struct next_if {
	template <typename N, typename T>
	struct apply : eval_if<
		typename x11::apply<Predicate, T>::type, next<N>, identity<N>
	> {};
};

}

template <typename...>
struct count_if;

template <>
struct count_if<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : count_if<T0, T1> {};
};

template <typename Tag>
struct lambda<count_if<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef count_if<> result_;
	typedef count_if<> type;
};

template <typename Sequence, typename Predicate>
struct count_if<Sequence, Predicate> : fold<
	Sequence, integral_constant<unsigned long, 0>,
	protect<detail::next_if<Predicate>>
>::type {};

namespace detail {

template <typename Tag>
struct count_impl {
	template <typename Sequence, typename T>
	struct apply : count_if<Sequence, same_as<T>> {};
};

template <>
struct count_impl<non_sequence_tag> {};

}

template <typename...>
struct count;

template <>
struct count<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : count<T0, T1> {};
};

template <typename Tag>
struct lambda<count<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef count<> result_;
	typedef count<> type;
};

template <typename Sequence, typename T>
struct count<Sequence, T>
: detail::count_impl<typename sequence_tag<Sequence>::type>
::template apply<Sequence, T> {};

}}}

#endif
