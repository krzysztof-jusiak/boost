/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/deque.hpp>
#include <boost/mpl/x11/size.hpp>
#include <boost/mpl/x11/front_back.hpp>
#include <boost/mpl/x11/push_pop.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(dequeue_0)
{
	typedef deque<> d0;
	typedef deque<char> d1;
	typedef deque<char, long> d2;
	typedef deque<char, char, char, char, char, char, char, char, int> d9;

	BOOST_CHECK_EQUAL((size<d0>::value), 0);
	BOOST_CHECK_EQUAL((size<d1>::value), 1);
	BOOST_CHECK_EQUAL((size<d2>::value), 2);
	BOOST_CHECK_EQUAL((size<d9>::value), 9);

	BOOST_CHECK((empty<d0>::value));
	BOOST_CHECK(!(empty<d1>::value));
	BOOST_CHECK(!(empty<d2>::value));
	BOOST_CHECK(!(empty<d9>::value));

	BOOST_CHECK((std::is_same<front<d1>::type, char>::value));
	BOOST_CHECK((std::is_same<back<d1>::type, char>::value));
	BOOST_CHECK((std::is_same<front<d2>::type, char>::value));
	BOOST_CHECK((std::is_same<back<d2>::type, long>::value));
	BOOST_CHECK((std::is_same<front<d9>::type, char>::value));
	BOOST_CHECK((std::is_same<back<d9>::type, int>::value));
}

BOOST_AUTO_TEST_CASE(dequeue_1)
{
	typedef deque<char, long> d2;

	typedef begin<d2>::type i1;
	typedef next<i1>::type i2;
	typedef next<i2>::type i3;

	BOOST_CHECK((std::is_same<deref<i1>::type, char>::value));
	BOOST_CHECK((std::is_same<deref<i2>::type, long>::value));
	BOOST_CHECK((std::is_same<i3, end<d2>::type>::value));
}

BOOST_AUTO_TEST_CASE(dequeue_2)
{
	typedef deque<> d0;

	typedef push_back<d0, int>::type d1;
	BOOST_CHECK((std::is_same<back<d1>::type, int>::value));

	typedef push_front<d1, char>::type d2;
	BOOST_CHECK((std::is_same<back<d2>::type, int>::value));
	BOOST_CHECK((std::is_same<front<d2>::type, char>::value));

	typedef push_back<d2, long>::type d3;
	BOOST_CHECK((std::is_same<back<d3>::type, long>::value));	
}

BOOST_AUTO_TEST_CASE(dequeue_3)
{
	typedef deque<> d0;
	typedef deque<char> d1;
	typedef deque<char, long> d2;
	typedef deque<char, char, char, char, char, char, char, char, int> d9;

	BOOST_CHECK_EQUAL((size<d0>::value), 0);
	BOOST_CHECK_EQUAL((size<d1>::value), 1);
	BOOST_CHECK_EQUAL((size<d2>::value), 2);
	BOOST_CHECK_EQUAL((size<d9>::value), 9);
}

}}}
