/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_NEXT_PRIOR_APR_03_2013_1500)
#define MPL_X11_NEXT_PRIOR_APR_03_2013_1500

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct next;

template <>
struct next<> {
	template <typename T0, typename... Tn>
	struct apply : next<T0> {};
};

template <typename T>
struct next<T> {
	typedef typename T::next type;
};

template <typename...>
struct prior;

template <>
struct prior<> {
	template <typename T0, typename... Tn>
	struct apply : prior<T0> {};
};

template <typename T>
struct prior<T> {
	typedef typename T::prior type;
};

}}}

#endif
