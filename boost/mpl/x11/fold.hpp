/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2001-2002 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_FOLD_APR_22_2013_2300)
#define MPL_X11_FOLD_APR_22_2013_2300

#include <boost/mpl/x11/apply.hpp>
#include <boost/mpl/x11/deref.hpp>
#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/begin_end.hpp>
#include <boost/mpl/x11/O1_size.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <
	long N, typename First, typename Last, typename State,
	typename ForwardOp
> struct fold_impl;

template <typename First, typename Last, typename State, typename ForwardOp>
struct fold_impl<0, First, Last, State, ForwardOp> {
	typedef First iter0;
	typedef State state0;
	typedef state0 state;
	typedef iter0 iterator;
};

template <typename First, typename Last, typename State, typename ForwardOp>
struct fold_impl<1, First, Last, State, ForwardOp> {
	typedef First iter0;
	typedef State state0;
	typedef typename apply<
		ForwardOp, state0, typename deref<iter0>::type
	>::type state1;
	typedef typename next<iter0>::type iter1;

	typedef state1 state;
	typedef iter1 iterator;
};

template <typename First, typename Last, typename State, typename ForwardOp>
struct fold_impl<2, First, Last, State, ForwardOp> {
	typedef First iter0;
	typedef State state0;
	typedef typename apply<
		ForwardOp, state0, typename deref<iter0>::type
	>::type state1;
	typedef typename next<iter0>::type iter1;
	typedef typename apply<
		ForwardOp, state1, typename deref<iter1>::type
	>::type state2;
	typedef typename next<iter1>::type iter2;

	typedef state2 state;
	typedef iter2 iterator;
};

template <typename First, typename Last, typename State, typename ForwardOp>
struct fold_impl<3, First, Last, State, ForwardOp> {
	typedef First iter0;
	typedef State state0;
	typedef typename apply<
		ForwardOp, state0, typename deref<iter0>::type
	>::type state1;
	typedef typename next<iter0>::type iter1;
	typedef typename apply<
		ForwardOp, state1, typename deref<iter1>::type
	>::type state2;
	typedef typename next<iter1>::type iter2;
	typedef typename apply<
		ForwardOp, state2, typename deref<iter2>::type
	>::type state3;
	typedef typename next<iter2>::type iter3;

	typedef state3 state;
	typedef iter3 iterator;
};

template <typename First, typename Last, typename State, typename ForwardOp>
struct fold_impl<4, First, Last, State, ForwardOp> {
	typedef First iter0;
	typedef State state0;
	typedef typename apply<
		ForwardOp, state0, typename deref<iter0>::type
	>::type state1;
	typedef typename next<iter0>::type iter1;
	typedef typename apply<
		ForwardOp, state1, typename deref<iter1>::type
	>::type state2;
	typedef typename next<iter1>::type iter2;
	typedef typename apply<
		ForwardOp, state2, typename deref<iter2>::type
	>::type state3;
	typedef typename next<iter2>::type iter3;
	typedef typename apply<
		ForwardOp, state3, typename deref<iter3>::type
	>::type state4;
	typedef typename next<iter3>::type iter4;

	typedef state4 state;
	typedef iter4 iterator;
};

template <
	long N, typename First, typename Last, typename State,
	typename ForwardOp
> struct fold_impl {
	typedef fold_impl<4, First, Last, State, ForwardOp> chunk_;

	typedef fold_impl<
		((N - 4) < 0 ? 0 : N - 4), typename chunk_::iterator, Last,
		typename chunk_::state, ForwardOp
	> res_;

	typedef typename res_::state state;
	typedef typename res_::iterator iterator;
};

template <typename First, typename Last, typename State, typename ForwardOp>
struct fold_impl<-1, First, Last, State, ForwardOp> : fold_impl<
	-1, typename next<First>::type, Last,
	typename apply<ForwardOp,State, typename deref<First>::type>::type,
	ForwardOp
> {};

template <typename Last, typename State, typename ForwardOp>
struct fold_impl<-1, Last, Last, State, ForwardOp> {
	typedef State state;
	typedef Last iterator;
};

}

template <typename...>
struct fold;

template <>
struct fold<> {
	template <typename T0, typename T1, typename T2, typename... Tn>
	struct apply : fold<T0, T1, T2> {};
};

template <typename Tag>
struct lambda<fold<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef fold<> result_;
	typedef fold<> type;
};

template <typename Sequence, typename State, typename ForwardOp>
struct fold<Sequence, State, ForwardOp> {
	typedef typename detail::fold_impl<
		O1_size<Sequence>::value, typename begin<Sequence>::type,
		typename end<Sequence>::type, State, ForwardOp
	>::state type;
};

}}}

#endif
