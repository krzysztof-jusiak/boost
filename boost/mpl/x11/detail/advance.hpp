/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_ADVANCE_APR_04_2013_1225)
#define MPL_X11_DETAIL_ADVANCE_APR_04_2013_1225

#include <boost/mpl/x11/sequence_tag_fwd.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/apply_wrap.hpp>
#include <boost/mpl/x11/comparison.hpp>
#include <boost/mpl/x11/arithmetic.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <long N> struct advance_backward;
template <long N> struct advance_forward;

template <>
struct advance_backward<0> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef iter0 type;
	};
};

template <>
struct advance_forward<0> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef iter0 type;
	};
};

template <>
struct advance_backward<1> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef typename prior<iter0>::type iter1;
		typedef iter1 type;
	};
};

template <>
struct advance_forward<1> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef typename next<iter0>::type iter1;
		typedef iter1 type;
	};
};

template <>
struct advance_backward<2> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef typename prior<iter0>::type iter1;
		typedef typename prior<iter1>::type iter2;
		typedef iter2 type;
	};
};

template <>
struct advance_forward<2> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef typename next<iter0>::type iter1;
		typedef typename next<iter1>::type iter2;
		typedef iter2 type;
	};
};

template <>
struct advance_backward<3> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef typename prior<iter0>::type iter1;
		typedef typename prior<iter1>::type iter2;
		typedef typename prior<iter2>::type iter3;
		typedef iter3 type;
	};
};

template <>
struct advance_forward<3> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef typename next<iter0>::type iter1;
		typedef typename next<iter1>::type iter2;
		typedef typename next<iter2>::type iter3;
		typedef iter3 type;
	};
};

template <>
struct advance_backward<4> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef typename prior<iter0>::type iter1;
		typedef typename prior<iter1>::type iter2;
		typedef typename prior<iter2>::type iter3;
		typedef typename prior<iter3>::type iter4;
		typedef iter4 type;
	};
};

template <>
struct advance_forward<4> {
	template <typename Iterator>
	struct apply {
		typedef Iterator iter0;
		typedef typename next<iter0>::type iter1;
		typedef typename next<iter1>::type iter2;
		typedef typename next<iter2>::type iter3;
		typedef typename next<iter3>::type iter4;
		typedef iter4 type;
	};
};

template <long N>
struct advance_backward {
	template <typename Iterator>
	struct apply {
		typedef typename apply_wrap<
			advance_backward<4>, Iterator
		>::type chunk_result_;

		typedef typename apply_wrap<
			advance_backward<((N - 4) < 0 ? 0 : N - 4)>,
			chunk_result_
		>::type type;
	};
};

template <long N>
struct advance_forward {
	template <typename Iterator>
	struct apply {
		typedef typename apply_wrap<
			advance_forward<4>, Iterator
		>::type chunk_result_;

		typedef typename apply_wrap<
			advance_forward<((N - 4) < 0 ? 0 : N - 4)>,
			chunk_result_
		>::type type;
	};
};

template <typename Tag>
struct advance_impl {
	template <typename Iterator, typename N>
	struct apply {
		typedef typename less<N, long_<0>>::type backward_;

		typedef typename if_<backward_, negate<N>, N>::type offset_;

		typedef typename if_<
			backward_,
			advance_backward<offset_::value>,
			advance_forward<offset_::value>
		>::type f_;

		typedef typename apply_wrap<f_,Iterator>::type type;
	};
};

}}}}

#endif
