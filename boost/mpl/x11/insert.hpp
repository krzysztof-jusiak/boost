/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_INSERT_APR_04_2013_1425)
#define MPL_X11_INSERT_APR_04_2013_1425

#include <boost/mpl/x11/detail/insert.hpp>

namespace boost { namespace mpl { namespace x11 {

template <>
struct insert<> {
	template <typename...>
	struct apply;

	template <typename T0, typename T1>
	struct apply<T0, T1> : insert<T0, T1> {};

	template <typename T0, typename T1, typename T2, typename... Tn>
	struct apply<T0, T1, T2, Tn...> : insert<T0, T1, T2> {};
};

template <typename Tag>
struct lambda<insert<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef insert<> result_;
	typedef insert<> type;
};

template<typename Sequence, typename T>
struct insert<Sequence, T>
: detail::insert_impl<typename sequence_tag<Sequence>::type>
	::template apply<Sequence, T> {};

template<typename Sequence, typename Pos, typename T>
struct insert<Sequence, Pos, T>
: detail::insert_impl<typename sequence_tag<Sequence>::type>
	::template apply<Sequence, Pos, T> {};

template <>
struct insert_range<> {
	template <typename T0, typename T1, typename T2, typename... Tn>
	struct apply : insert_range<T0, T1, T2> {};
};

template <typename Tag>
struct lambda<insert_range<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef insert_range<> result_;
	typedef insert_range<> type;
};

template <typename Sequence, typename Pos, typename Range>
struct insert_range<Sequence, Pos, Range>
: detail::insert_range_impl<typename sequence_tag<Sequence>::type>
	::template apply<Sequence, Pos, Range> {};

}}}

#endif
