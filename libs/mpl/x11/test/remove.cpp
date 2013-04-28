/*==============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/remove.hpp>
#include <boost/mpl/x11/vector.hpp>
#include <boost/mpl/x11/equal.hpp>
#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/size.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(remove_0)
{
	typedef vector<int, float, char, float, float, double> types;
	typedef remove<types, float>::type result;
	typedef vector<int, char, double> answer;
	BOOST_CHECK((equal<result, answer>::value));
}

BOOST_AUTO_TEST_CASE(remove_1)
{
	typedef list_c<int, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9> numbers;
	typedef list_c<int, 4, 3, 2, 1, 0>::type answer;
	typedef remove_if<
		numbers, greater<arg<-1>, int_<4>>, front_inserter<list_c<int>>
	>::type result;

	BOOST_CHECK_EQUAL((size<result>::value), 5);
	BOOST_CHECK((equal<result, answer>::value));
}

BOOST_AUTO_TEST_CASE(remove_2)
{
	typedef list<
		int, float, long, float, char, long, double, double
	> types;
	typedef list<int, long, char, long>::type answer;
	typedef reverse_remove_if<
		types, is_floating_point<arg<-1>>, front_inserter<list<>>
	>::type result;

	BOOST_CHECK_EQUAL((size<result>::value), 4);
	BOOST_CHECK((equal<result,answer>::value));
}

}}}
