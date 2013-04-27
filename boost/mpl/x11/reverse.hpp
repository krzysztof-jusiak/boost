/*==============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_REVERSE_APR_27_2013_2300)
#define MPL_X11_REVERSE_APR_27_2013_2300

#include <boost/mpl/x11/copy.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct reverse;

template <>
struct reverse<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : reverse<T0> {};
};

template <typename Tag>
struct lambda<reverse<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef reverse<> result_;
	typedef reverse<> type; 
};

template <typename Sequence>
struct reverse<Sequence> : reverse_copy<Sequence> {};

template <typename Sequence, typename Inserter>
struct reverse<Sequence, Inserter> : reverse_copy<Sequence, Inserter> {};



}}}

#endif
