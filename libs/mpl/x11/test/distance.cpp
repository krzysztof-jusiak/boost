/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/distance.hpp>
#include <boost/mpl/x11/range_c.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(distance_0)
{
	typedef list<char, short, int, long>::type list;
	typedef begin<list>::type first;
	typedef end<list>::type last;

	BOOST_CHECK_EQUAL((distance<first, last>::value), 4);
}

BOOST_AUTO_TEST_CASE(distance_1)
{
	typedef range_c<int, 0, 10>::type range;
	typedef begin<range>::type first;
	typedef end<range>::type last;

	BOOST_CHECK_EQUAL((distance<first, last>::value), 10);
}

}}}
