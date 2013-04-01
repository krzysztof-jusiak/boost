/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_IF_APR_01_2013_1400)
#define MPL_X11_IF_APR_01_2013_1400

#if defined(_MSC_VER)
#pragma once
#endif

#include <type_traits>

#if defined(BOOST_TEST_MODULE)
#include_next<boost/mpl/if.hpp>
#endif

namespace boost { namespace mpl { namespace x11 {

template <bool C, typename T1, typename T2>
struct if_c {
	typedef typename std::conditional<C, T1, T2>::type type;
};

template <typename T1, typename T2, typename T3>
struct if_ {
	typedef typename std::conditional<T1::value, T2, T3>::type type;
};

}}}

#endif
