/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/logical.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(logical)
{
	using std::true_type;
	using std::false_type;
	struct unknown;

	BOOST_CHECK((and_<true_type, true_type>::value));
	BOOST_CHECK(!(and_<false_type, true_type>::value));
	BOOST_CHECK(!(and_<true_type, false_type>::value));
	BOOST_CHECK(!(and_<false_type, false_type>::value));
	BOOST_CHECK(!(and_<false_type, unknown>::value));
	BOOST_CHECK(!(and_<false_type, unknown, unknown>::value));

	BOOST_CHECK((or_<true_type, true_type>::value));
	BOOST_CHECK((or_<false_type, true_type>::value));
	BOOST_CHECK((or_<true_type, false_type>::value));
	BOOST_CHECK(!(or_<false_type, false_type>::value));
	BOOST_CHECK((or_<true_type, unknown>::value));
	BOOST_CHECK((or_<true_type, unknown, unknown>::value));

	BOOST_CHECK(!(not_<true_type>::value));
	BOOST_CHECK((not_<false_type>::value));
}

}}}
