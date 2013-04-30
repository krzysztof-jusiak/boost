/*=============================================================================
    Copyright (c) 2009      Larry Evans
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_UNPACK_ARGS_APR_12_2013_1730)
#define MPL_X11_UNPACK_ARGS_APR_12_2013_1730

#include <boost/mpl/x11/package_range_c.hpp>
#include <boost/mpl/x11/apply.hpp>
#include <boost/mpl/x11/size.hpp>
#include <boost/mpl/x11/at.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Tpack, typename F, typename Tn>
struct unpack_args_impl;

template <long... Cn, typename F, typename Tn>
struct unpack_args_impl<package_c<long, Cn...>, F, Tn> : apply<
	F, typename at_c<Tn, Cn>::type...
> {};

}

template <typename F>
struct unpack_args {
	template <typename Tn>
	struct apply
	: detail::unpack_args_impl<
		typename package_range_c<
			long, long(0), long(size<Tn>::value)
		>::type, F, Tn
	> {};
};

template <typename T0, typename Tag>
struct lambda<unpack_args<T0>, Tag, long_<1>> {
	typedef false_type is_le;
	typedef unpack_args<T0> result_;
	typedef result_ type;
};

}}}

#endif
