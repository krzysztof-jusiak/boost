/*=============================================================================
    Copyright (c) 2000-2002 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_FIND_APR_04_2013_1545)
#define MPL_X11_FIND_APR_04_2013_1545

#include <boost/mpl/x11/detail/iter_apply.hpp>
#include <boost/mpl/x11/arg.hpp>
#include <boost/mpl/x11/same_as.hpp>
#include <boost/mpl/x11/identity.hpp>
#include <boost/mpl/x11/iter_fold_if.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Predicate>
struct find_if_pred {
	template <typename Iterator>
	struct apply {
		typedef not_<iter_apply<Predicate, Iterator>> type;
	};
};

}

template <typename...>
struct find_if;

template <>
struct find_if<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : find_if<T0, T1> {};
};

template <typename Tag>
struct lambda<find_if<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef find_if<> result_;
	typedef find_if<> type;
};

template <typename Sequence, typename Predicate>
struct find_if<Sequence, Predicate> {
	typedef typename iter_fold_if<
		Sequence, void, arg<0>,
		protect<detail::find_if_pred<Predicate>>
	>::type result_;

	typedef typename second<result_>::type type;
};

template <typename...>
struct find;

template <>
struct find<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : find<T0, T1> {};
};

template <typename Tag>
struct lambda<find<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef find<> result_;
	typedef find<> type;
};

template <typename Sequence, typename T>
struct find<Sequence, T> : find_if <Sequence, same_as<T>> {};

}}}

#endif
