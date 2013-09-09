/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_FRONT_BACK_APR_03_2013_1230)
#define MPL_X11_FRONT_BACK_APR_03_2013_1230

#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/sequence_tag.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Tag>
struct front_impl {
	template <typename Sequence>
	struct apply {
		typedef typename begin<Sequence>::type iter_;
		typedef typename deref<iter_>::type type;
	};
};

template <>
struct front_impl<non_sequence_tag> {};

template <typename Tag>
struct back_impl {
	template <typename Sequence>
	struct apply {
		typedef typename end<Sequence>::type end_;
		typedef typename prior<end_>::type last_;
		typedef typename deref<last_>::type type;
	};
};

template <>
struct back_impl<non_sequence_tag> {};

}

template <>
struct front<> {
	template <typename T0, typename... Tn>
	struct apply : front<T0> {};
};

template <typename Tag>
struct lambda<front<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef front<> result_;
	typedef front<> type;
};

template <typename Sequence>
struct front<Sequence> : detail::front_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence>
{};

template <>
struct back<> {
	template <typename T0, typename... Tn>
	struct apply : back<T0> {};
};

template <typename Tag>
struct lambda<back<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef back<> result_;
	typedef back<> type;
};

template <typename Sequence>
struct back<Sequence> : detail::back_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence>
{};

}}}

#endif
