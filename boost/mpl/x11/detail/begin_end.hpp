/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_BEGIN_END_APR_03_2013_1430)
#define MPL_X11_DETAIL_BEGIN_END_APR_03_2013_1430

#include <boost/mpl/x11/sequence_tag_fwd.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/detail/has_begin.hpp>
#include <boost/mpl/x11/void.hpp>
#include <boost/mpl/x11/if.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename Sequence>
struct begin_type {
	typedef typename Sequence::begin type;
};

template <typename Sequence>
struct end_type {
	typedef typename Sequence::end type;
};

template <typename Tag>
struct begin_impl {
	template <typename Sequence>
	struct apply {
		typedef typename eval_if<
			has_begin<Sequence>,
			begin_type<Sequence>,
			void_
		>::type type;
	};
};

template <typename Tag>
struct end_impl {
	template <typename Sequence>
	struct apply {
		typedef typename eval_if<
			has_begin<Sequence>,
			end_type<Sequence>,
			void_
		>::type type;
	};
};

template <>
struct begin_impl<nested_begin_end_tag> {
	template <typename Sequence>
	struct apply {
		typedef typename Sequence::begin type;
	};
};

template <>
struct end_impl<nested_begin_end_tag> {
	template <typename Sequence>
	struct apply {
		typedef typename Sequence::end type;
	};
};

template <>
struct begin_impl<non_sequence_tag> {
	template <typename Sequence>
	struct apply {
		typedef void_ type;
	};
};

template <>
struct end_impl<non_sequence_tag> {
	template <typename Sequence>
	struct apply {
		typedef void_ type;
	};
};

}}}}

#endif
