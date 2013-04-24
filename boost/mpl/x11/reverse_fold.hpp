/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2001-2002 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_REVERSE_FOLD_APR_08_2013_1800)
#define MPL_X11_REVERSE_FOLD_APR_08_2013_1800

#include <boost/mpl/x11/apply.hpp>
#include <boost/mpl/x11/O1_size.hpp>
#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/deref.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <
	long N, typename First, typename Last, typename State,
	typename BackwardOp, typename ForwardOp
> struct reverse_fold_impl;

template <
	typename First, typename Last, typename State, typename BackwardOp,
	typename ForwardOp
> struct reverse_fold_impl<0, First, Last, State, BackwardOp, ForwardOp> {
	typedef First iter0;
	typedef State fwd_state0;
	typedef fwd_state0 bkwd_state0;
	typedef bkwd_state0 state;
	typedef iter0 iterator;
};

template <
	typename First, typename Last, typename State, typename BackwardOp,
	typename ForwardOp
> struct reverse_fold_impl<1, First, Last, State, BackwardOp, ForwardOp> {
	typedef First iter0;
	typedef State fwd_state0;
	typedef typename apply<
		ForwardOp, fwd_state0, typename deref<iter0>::type
	>::type fwd_state1;
	typedef typename next<iter0>::type iter1;

	typedef fwd_state1 bkwd_state1;
	typedef typename apply<
		BackwardOp, bkwd_state1, typename deref<iter0>::type
	>::type bkwd_state0;
	typedef bkwd_state0 state;
	typedef iter1 iterator;
};

template <
	typename First, typename Last, typename State, typename BackwardOp,
	typename ForwardOp
> struct reverse_fold_impl<2, First, Last, State, BackwardOp, ForwardOp> {
	typedef First iter0;
	typedef State fwd_state0;
	typedef typename apply<
		ForwardOp, fwd_state0, typename deref<iter0>::type
	>::type fwd_state1;
	typedef typename next<iter0>::type iter1;
	typedef typename apply<
		ForwardOp, fwd_state1, typename deref<iter1>::type
	>::type fwd_state2;
	typedef typename next<iter1>::type iter2;

	typedef fwd_state2 bkwd_state2;
	typedef typename apply<
		BackwardOp, bkwd_state2, typename deref<iter1>::type
	>::type bkwd_state1;
	typedef typename apply<
		BackwardOp, bkwd_state1, typename deref<iter0>::type
	>::type bkwd_state0;

	typedef bkwd_state0 state;
	typedef iter2 iterator;
};

template <
	typename First, typename Last, typename State, typename BackwardOp,
	typename ForwardOp
> struct reverse_fold_impl<3, First, Last, State, BackwardOp, ForwardOp> {
	typedef First iter0;
	typedef State fwd_state0;
	typedef typename apply<
		ForwardOp, fwd_state0, typename deref<iter0>::type
	>::type fwd_state1;
	typedef typename next<iter0>::type iter1;
	typedef typename apply<
		ForwardOp, fwd_state1, typename deref<iter1>::type
	>::type fwd_state2;
	typedef typename next<iter1>::type iter2;
	typedef typename apply<
		ForwardOp, fwd_state2, typename deref<iter2>::type
	>::type fwd_state3;
	typedef typename next<iter2>::type iter3;

	typedef fwd_state3 bkwd_state3;
	typedef typename apply<
		BackwardOp, bkwd_state3, typename deref<iter2>::type
	>::type bkwd_state2;
	typedef typename apply<
		BackwardOp, bkwd_state2, typename deref<iter1>::type
	>::type bkwd_state1;
	typedef typename apply<
		BackwardOp, bkwd_state1, typename deref<iter0>::type
	>::type bkwd_state0;

	typedef bkwd_state0 state;
	typedef iter3 iterator;
};


template <
	typename First, typename Last, typename State, typename BackwardOp,
	typename ForwardOp
> struct reverse_fold_impl<4, First, Last, State, BackwardOp, ForwardOp> {
	typedef First iter0;
	typedef State fwd_state0;
	typedef typename apply<
		ForwardOp, fwd_state0, typename deref<iter0>::type
	>::type fwd_state1;
	typedef typename next<iter0>::type iter1;
	typedef typename apply<
		ForwardOp, fwd_state1, typename deref<iter1>::type
	>::type fwd_state2;
	typedef typename next<iter1>::type iter2;
	typedef typename apply<
		ForwardOp, fwd_state2, typename deref<iter2>::type
	>::type fwd_state3;
	typedef typename next<iter2>::type iter3;
	typedef typename apply<
		ForwardOp, fwd_state3, typename deref<iter3>::type
	>::type fwd_state4;
	typedef typename next<iter3>::type iter4;

	typedef fwd_state4 bkwd_state4;
	typedef typename apply<
		BackwardOp, bkwd_state4, typename deref<iter3>::type
	>::type bkwd_state3;
	typedef typename apply<
		BackwardOp, bkwd_state3, typename deref<iter2>::type
	>::type bkwd_state2;
	typedef typename apply<
		BackwardOp, bkwd_state2, typename deref<iter1>::type
	>::type bkwd_state1;
	typedef typename apply<
		BackwardOp, bkwd_state1, typename deref<iter0>::type
	>::type bkwd_state0;

	typedef bkwd_state0 state;
	typedef iter4 iterator;
};

template <
	long N, typename First, typename Last, typename State,
	typename BackwardOp, typename ForwardOp
> struct reverse_fold_impl {
	typedef First iter0;
	typedef State fwd_state0;
	typedef typename apply<
		ForwardOp, fwd_state0, typename deref<iter0>::type
	>::type fwd_state1;
	typedef typename next<iter0>::type iter1;
	typedef typename apply<
		ForwardOp, fwd_state1, typename deref<iter1>::type
	>::type fwd_state2;
	typedef typename next<iter1>::type iter2;
	typedef typename apply<
		ForwardOp, fwd_state2, typename deref<iter2>::type
	>::type fwd_state3;
	typedef typename next<iter2>::type iter3;
	typedef typename apply<
		ForwardOp, fwd_state3, typename deref<iter3>::type
	>::type fwd_state4;
	typedef typename next<iter3>::type iter4;

	typedef reverse_fold_impl<
		((N - 4) < 0 ? 0 : N - 4), iter4 , Last, fwd_state4,
		BackwardOp, ForwardOp
	> nested_chunk;

	typedef typename nested_chunk::state bkwd_state4;
	typedef typename apply<
		BackwardOp, bkwd_state4, typename deref<iter3>::type
	>::type bkwd_state3;
	typedef typename apply<
		BackwardOp, bkwd_state3, typename deref<iter2>::type
	>::type bkwd_state2;
	typedef typename apply<
		BackwardOp, bkwd_state2, typename deref<iter1>::type
	>::type bkwd_state1;
	typedef typename apply<
		BackwardOp, bkwd_state1, typename deref<iter0>::type
	>::type bkwd_state0;

	typedef bkwd_state0 state;
	typedef typename nested_chunk::iterator iterator;
};

template <
	typename First, typename Last, typename State, typename BackwardOp,
	typename ForwardOp
> struct reverse_fold_impl<-1, First, Last, State, BackwardOp, ForwardOp> {
	typedef reverse_fold_impl<
		-1, typename next<First>::type, Last,
		typename apply<
			ForwardOp, State, typename deref<First>::type
		>::type, BackwardOp, ForwardOp
	> nested_step;

	typedef typename apply<
		BackwardOp, typename nested_step::state,
		typename deref<First>::type
	>::type state;

	typedef typename nested_step::iterator iterator;
};

template <
	typename Last, typename State, typename BackwardOp, typename ForwardOp
> struct reverse_fold_impl<-1, Last, Last, State, BackwardOp, ForwardOp> {
	typedef State state;
	typedef Last iterator;
};

}

template <typename...>
struct reverse_fold;

template <>
struct reverse_fold<> {
	template <typename T0, typename T1, typename T2, typename... Tn>
	struct apply : reverse_fold<T0, T1, T2> {};
};

template <typename Tag>
struct lambda<reverse_fold<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef reverse_fold<> result_;
	typedef reverse_fold<> type;
};

template <typename Sequence, typename State, typename BackwardOp>
struct reverse_fold<Sequence, State, BackwardOp> {
	typedef typename detail::reverse_fold_impl<
		O1_size<Sequence>::value,
		typename begin<Sequence>::type,
		typename end<Sequence>::type,
		State, BackwardOp, arg<0>
	>::state type;
};

template <
	typename Sequence, typename State, typename BackwardOp,
	typename ForwardOp
> struct reverse_fold<Sequence, State, BackwardOp, ForwardOp> {
	typedef typename detail::reverse_fold_impl<
		O1_size<Sequence>::value,
		typename begin<Sequence>::type,
		typename end<Sequence>::type,
		State, BackwardOp, ForwardOp
	>::state type;
};

}}}

#endif
