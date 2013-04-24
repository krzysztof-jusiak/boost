/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/equal.hpp>
#include <boost/mpl/x11/list.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(equal_0)
{
	typedef list<int, float, long, double, char, long, double, float> list1;
	typedef list<int, float, long, double, char, long, double, float> list2;
	typedef list<int, float, long, double, char, long, double, short> list3;
	typedef list<int, float, long, double, char, long, double> list4;

	BOOST_CHECK((equal<list1, list2>::value));
	BOOST_CHECK((equal<list2, list1>::value));
	BOOST_CHECK(!(equal<list2, list3>::value));
	BOOST_CHECK(!(equal<list3, list4>::value));
	BOOST_CHECK(!(equal<list4, list3>::value));
}

}}}
