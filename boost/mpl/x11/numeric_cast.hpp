/*=============================================================================
    Copyright (c) 2003-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_NUMERIC_CAST_APR_05_2013_1430)
#define MPL_X11_NUMERIC_CAST_APR_05_2013_1430

#include <boost/mpl/x11/apply_wrap.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename SourceTag, typename TargetTag>
struct numeric_cast {
	template <typename N>
	struct apply;
};

namespace detail {

template <typename F, typename Tag0, typename Tag1>
struct cast1st_impl {
	template <typename N0, typename N1>
	struct apply : apply_wrap<
		F,
		typename apply_wrap<numeric_cast<Tag0, Tag1>, N0>::type,
		N1
	> {};
};

template <typename F, typename Tag0, typename Tag1>
struct cast2nd_impl {
	template <typename N0, typename N1>
	struct apply : apply_wrap<
		F,
		N0,
		typename apply_wrap<numeric_cast<Tag1, Tag0>, N1>::type
	> {};
};

}

}}}

#endif
