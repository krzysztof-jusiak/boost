/*=============================================================================
    Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>

    Based on original implementation:
        Copyright (c) 2000-2004 Aleksey Gurtovoy

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_LIST_APR_02_2013_1710)
#define MPL_X11_LIST_APR_02_2013_1710

#include <boost/mpl/x11/arithmetic.hpp>
#include <boost/mpl/x11/size_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct list_tag;
struct l_iter_tag;

template <typename Size, typename T, typename Next>
struct l_item {
	typedef list_tag tag;
	typedef l_item type;
	typedef Size size;
	typedef T item;
	typedef Next next;
};

struct l_end {
	typedef list_tag tag;
	typedef l_end type;
	typedef long_<0> size;
};

template <>
struct size_impl<list_tag> {
	template <typename List> struct apply : List::size {};
};

}

template <typename...>
struct list;

template <>
struct list<> : detail::l_end {
	typedef detail::l_end type;
};

template <typename T0>
struct list<T0> : detail::l_item<long_<1>, T0, detail::l_end> {
	typedef list<T0> type;
};

template <typename T0, typename T1>
struct list<T0, T1> : detail::l_item<long_<2>, T0, list<T1>> {
	typedef list<T0, T1> type;
};

template <typename T0, typename T1, typename... Tn>
struct list<T0, T1, Tn...> : detail::l_item<
	plus<long_<1>, typename list<T1, Tn...>::size>,
	T0, list<T1, Tn...>
> {
	typedef list<T0, T1, Tn...> type;
};

}}}

#endif
