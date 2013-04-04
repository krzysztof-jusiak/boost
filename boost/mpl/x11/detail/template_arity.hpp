/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_TEMPLATE_ARITY_APR_04_2013_1700)
#define MPL_X11_DETAIL_TEMPLATE_ARITY_APR_04_2013_1700


namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename F>
struct template_arity {
	static long const value = 0;
	typedef long_<value> type;
};

}}}}

#endif
