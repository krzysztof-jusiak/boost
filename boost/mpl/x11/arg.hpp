/*=============================================================================
    Copyright (c) 2001-2002 Peter Dimov
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ARG_APR_04_2013_1600)
#define MPL_X11_ARG_APR_04_2013_1600

#include <boost/mpl/x11/void.hpp>
#include <boost/mpl/x11/if.hpp>

namespace boost { namespace mpl { namespace x11 {

template <long N, long Pos = 0>
struct arg {
	static long const value = N;
	typedef arg<N + 1> next;

	template <typename...>
	struct apply;

	template <typename T0>
	struct apply<T0> {
		typedef typename if_c<!(N - Pos), T0, void_>::type type;
	};

	template <typename T0, typename... Tn>
	struct apply<T0, Tn...> {
		typedef typename if_c<
			!(N - Pos), T0,
			typename arg<
				N, Pos + 1
			>::template apply<Tn...>::type
		>::type type;
	};
};

template <>
struct arg<-1> {
	static long const value = -1;

	template <typename...>
	struct apply;

	template <typename T0>
	struct apply<T0> {
		typedef T0 type;
	};

	template <typename T0, typename... Tn>
	struct apply<T0, Tn...> {
		typedef T0 type;
	};
};

template <typename T>
struct is_placeholder : false_type {};

template <long N>
struct is_placeholder<arg<N, 0>> : true_type {};

}}}

#endif
