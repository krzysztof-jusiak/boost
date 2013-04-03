/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2000-2003 Peter Dimov
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_TYPE_WRAPPER_APR_03_2013_1100)
#define MPL_X11_DETAIL_TYPE_WRAPPER_APR_03_2013_1100

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename T>
struct type_wrapper {
	typedef T type;
};

template <typename T>
struct wrapped_type;

template <typename T>
struct wrapped_type <type_wrapper<T>> {
	typedef T type;
};

template <typename T>
static T const &ptr_to_ref(T *);

}}}}

#endif
