/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2001-2002 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_REVERSE_FOLD_APR_08_2013_1800)
#define MPL_X11_REVERSE_FOLD_APR_08_2013_1800

#include <boost/mpl/x11/detail/reverse_fold.hpp>
#include <boost/mpl/x11/O1_size.hpp>

namespace boost { namespace mpl { namespace x11 {

template <
	typename Sequence, typename State, typename BackwardOp,
	typename ForwardOp = arg<0>
> struct reverse_fold {
	typedef typename detail::reverse_fold_impl<
		O1_size<Sequence>::value,
		typename begin<Sequence>::type,
		typename end<Sequence>::type,
		State, BackwardOp, ForwardOp
	>::state type;
};

}}}

#endif
