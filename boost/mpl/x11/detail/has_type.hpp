/*=============================================================================
    Copyright (c) 2002-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_HAS_TYPE_APR_03_2013_1420)
#define MPL_X11_DETAIL_HAS_TYPE_APR_03_2013_1420

#include <boost/mpl/x11/integral.hpp>
#include <boost/mpl/x11/detail/type_wrapper.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename T>
struct has_type {
	template <typename U>
	static true_type test(
		type_wrapper<U> const volatile *,
		type_wrapper<typename U::type> * = 0
	);

	static false_type test(...);

	typedef decltype(test(static_cast<type_wrapper<T> *>(nullptr))) type;

	static const bool value = type::value;
};

}}}}

#endif
