/*==============================================================================
    Copyright (c) 2002-2003 Eric Friedman
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/min_max_element.hpp>
#include <boost/mpl/x11/list.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(min_max_element_0)
{
	typedef list_c<int,3, 4, 2, 0, -5, 8, -1, 7>::type numbers;
	typedef max_element<numbers>::type max_iter;
	typedef min_element<numbers>::type min_iter;

	BOOST_CHECK_EQUAL((deref<max_iter>::type::value), 8);
	BOOST_CHECK_EQUAL((deref<min_iter>::type::value), -5);
}

}}}
