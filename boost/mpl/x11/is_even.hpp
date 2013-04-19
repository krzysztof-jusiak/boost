/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_IS_EVEN_APR_19_2013_1730)
#define MPL_X11_IS_EVEN_APR_19_2013_1730

#include <boost/mpl/x11/integral.hpp>
#include <boost/mpl/x11/lambda_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct is_even;

template <>
struct is_even<> {
	template <typename T0, typename... Tn>
	struct apply : is_even<T0> {};
};

template <typename Tag>
struct lambda<is_even<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef is_even<> result_;
	typedef is_even<> type;
};

template <typename N>
struct is_even<N> : bool_<((N::value % 2) == 0)> {};

}}}

#endif
