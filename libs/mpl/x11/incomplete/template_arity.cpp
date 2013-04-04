/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/detail/template_arity.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(template_arity)
{
	struct my {};
	template <typename T0> struct my1 {};
	template <typename T0, typename T1 = void> struct my2 {};

	BOOST_CHECK_EQUAL((detail::template_arity<my>::value), -1);
	BOOST_CHECK_EQUAL((detail::template_arity<my1<int>>::value), 1);
	BOOST_CHECK_EQUAL((detail::template_arity<my2<int, long>>::value), 2);
	BOOST_CHECK_EQUAL((detail::template_arity<my2<int>>::value), 2);
}

}}}
