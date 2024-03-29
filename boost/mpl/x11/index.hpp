/*=============================================================================
    Copyright (c) 2003-2004 Aleksey Gurtovoy
    Copyright (c) 2003      Eric Friedman
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_INDEX_APR_25_2013_2300)
#define MPL_X11_INDEX_APR_25_2013_2300

#include <boost/mpl/x11/find.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct index_if;

template <>
struct index_if<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : index_if<T0, T1> {};
};

template <typename Tag>
struct lambda<index_if<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef index_if<> result_;
	typedef index_if<> type;
};

template <typename Sequence, typename Predicate>
struct index_if<Sequence, Predicate> {
	typedef typename iter_fold_if<
		Sequence, long_<0>, next<>, detail::find_if_pred<Predicate>
	>::type result_;

	typedef typename end<Sequence>::type not_found_;
	typedef typename first<result_>::type result_index_;
	typedef typename second<result_>::type result_iterator_;

	typedef typename if_<
		std::is_same<result_iterator_, not_found_>, void_, result_index_
	>::type type;
};

template <typename...>
struct index_of;

template <>
struct index_of<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : index_of<T0, T1> {};
};

template <typename Tag>
struct lambda<index_of<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef index_of<> result_;
	typedef index_of<> type;
};

template <typename Sequence, typename T>
struct index_of<Sequence, T> : index_if<Sequence, same_as<T>> {};

}}}

#endif
