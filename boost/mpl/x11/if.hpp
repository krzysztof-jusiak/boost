/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_IF_APR_01_2013_1400)
#define MPL_X11_IF_APR_01_2013_1400

#include <type_traits>

namespace boost { namespace mpl { namespace x11 {

template <bool C, typename T0, typename T1>
struct if_c {
	typedef typename std::conditional<C, T0, T1>::type type;
};

template <typename Tc, typename T0, typename T1>
struct if_ {
	typedef typename std::conditional<
		static_cast<bool>(Tc::value), T0, T1
	>::type type;
};

template <bool C, typename T0, typename T1>
struct eval_if_c {
	typedef typename if_c<C, T0, T1>::type f_;
	typedef typename f_::type type;
};

template <typename Tc, typename T0, typename T1>
struct eval_if {
	typedef typename if_<Tc, T0, T1>::type f_;
	typedef typename f_::type type;
};

}}}

#endif
