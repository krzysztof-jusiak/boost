/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_SEQUENCE_TAG_APR_02_2013_1800)
#define MPL_X11_SEQUENCE_TAG_APR_02_2013_1800

#include <boost/mpl/x11/sequence_tag_fwd.hpp>
#include <boost/mpl/x11/detail/has_tag.hpp>
#include <boost/mpl/x11/detail/has_begin.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <bool has_tag_, bool has_begin_>
struct sequence_tag_impl {
	template <typename Sequence> struct result_;
};

template <>
struct sequence_tag_impl<true, true> {
	template <typename Sequence> struct result_ {
		typedef typename Sequence::tag type;
	};
};

template <>
struct sequence_tag_impl<true, false> {
	template <typename Sequence> struct result_ {
		typedef typename Sequence::tag type;
	};
};

template <>
struct sequence_tag_impl<false, true> {
	template <typename Sequence> struct result_ {
		typedef nested_begin_end_tag type;
	};
};

template <>
struct sequence_tag_impl<false, false> {
	template <typename Sequence> struct result_ {
		typedef non_sequence_tag type;
	};
};

}

template <typename Sequence>
struct sequence_tag : detail::sequence_tag_impl<
	detail::has_tag<Sequence>::value,
	detail::has_begin<Sequence>::value
>::template result_<Sequence> {};

}}}

#endif
