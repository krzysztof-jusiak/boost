/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/begin_end.hpp>
#include <boost/mpl/x11/push_pop.hpp>
#include <boost/mpl/x11/front_back.hpp>
#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/size.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(list_0)
{
	typedef list<> l0;
	typedef list<char> l1;
	typedef list<long, char> l2;
	typedef list<char, char, char, char, char, char, char, char, char> l9;

	BOOST_CHECK_EQUAL((size<l0>::value), 0);
	BOOST_CHECK_EQUAL((size<l1>::value), 1);
	BOOST_CHECK_EQUAL((size<l2>::value), 2);
	BOOST_CHECK_EQUAL((size<l9>::value), 9);

	BOOST_CHECK((empty<l0>::value));
	BOOST_CHECK(!(empty<l1>::value));
	BOOST_CHECK(!(empty<l2>::value));
	BOOST_CHECK(!(empty<l9>::value));

	BOOST_CHECK((std::is_same<front<l1>::type, char>::value));
	BOOST_CHECK((std::is_same<front<l2>::type, long>::value));
	BOOST_CHECK((std::is_same<front<l9>::type, char>::value));
}

BOOST_AUTO_TEST_CASE(list_1)
{
	typedef x11::list<char, long> l2;

	typedef x11::begin<l2>::type i1;
	typedef next<i1>::type i2;
	typedef next<i2>::type i3;

	BOOST_CHECK((std::is_same<deref<i1>::type, char>::value));
	BOOST_CHECK((std::is_same<deref<i2>::type, long>::value));
	BOOST_CHECK((std::is_same<i3, end<l2>::type>::value));
}

BOOST_AUTO_TEST_CASE(list_2)
{
	typedef list<> l0;
	typedef push_front<l0, char>::type l1;

	BOOST_CHECK((std::is_same<front<l1>::type, char>::value));

	typedef push_front<l1, long>::type l2;
	BOOST_CHECK((std::is_same<front<l2>::type, long>::value));
}

}}}
