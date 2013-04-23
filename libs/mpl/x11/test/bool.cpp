/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/integral.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(bool_0)
{

#define BOOL_TEST(c) \
	{ BOOST_CHECK((std::is_same<bool_<c>::value_type, bool>::value)); } \
	{ BOOST_CHECK((std::is_same<bool_<c>, c##_type>::value )); }        \
	{ BOOST_CHECK((std::is_same<bool_<c>::type, bool_<c>>::value)); }   \
	{ BOOST_CHECK_EQUAL((bool_<c>::value), c); }                        \
	{ BOOST_CHECK_EQUAL((bool_<c>()), c); }

	BOOL_TEST(true);
	BOOL_TEST(false);
}

}}}
