/*=============================================================================
    Copyright (c) 2002-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_UNPACK_ARGS_APR_12_2013_1730)
#define MPL_X11_UNPACK_ARGS_APR_12_2013_1730

#include <boost/mpl/x11/apply.hpp>
#include <boost/mpl/x11/size.hpp>
#include <boost/mpl/x11/at.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <long size, typename F, typename Args>
struct unpack_args_impl;

template <typename F, typename Args>
struct unpack_args_impl<0, F, Args>
: apply<F> {};

template <typename F, typename Args>
struct unpack_args_impl<1, F, Args>
: apply<F, typename at_c<Args, 0>::type> {};

template <typename F, typename Args>
struct unpack_args_impl<2, F, Args>
: apply<
	F, typename at_c<Args, 0>::type, typename at_c<Args, 1>::type
> {};

template <typename F, typename Args>
struct unpack_args_impl<3, F, Args>
: apply<
	F, typename at_c<Args, 0>::type, typename at_c<Args, 1>::type,
	typename at_c<Args, 2>::type
> {};

template <typename F, typename Args>
struct unpack_args_impl<4, F, Args>
: apply<
	F, typename at_c<Args, 0>::type, typename at_c<Args, 1>::type,
	typename at_c<Args, 2>::type, typename at_c<Args, 3>::type
> {};

template <typename F, typename Args>
struct unpack_args_impl<5, F, Args>
: apply<
	F, typename at_c<Args, 0>::type, typename at_c<Args, 1>::type,
	typename at_c<Args, 2>::type, typename at_c<Args, 3>::type,
	typename at_c<Args, 4>::type
> {};

}

template <typename F>
struct unpack_args {
	template <typename Args>
	struct apply
	: detail::unpack_args_impl<size<Args>::value, F, Args> {};
};

template <typename T0, typename Tag>
struct lambda<unpack_args<T0>, Tag, long_<1>> {
	typedef false_type is_le;
	typedef unpack_args<T0> result_;
	typedef result_ type;
};

}}}

#endif
