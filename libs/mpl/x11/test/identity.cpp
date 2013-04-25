/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/identity.hpp>
#include <boost/mpl/x11/apply.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(identity_0)
{
	typedef apply<identity<>, char>::type t1;
	typedef apply<identity<arg<0>>, int>::type t2;

	BOOST_CHECK((std::is_same<t1, char>::value));
	BOOST_CHECK((std::is_same<t2, int>::value));
}

BOOST_AUTO_TEST_CASE(identity_1)
{
	typedef apply<make_identity<>, char>::type t1;
	typedef apply<make_identity<arg<0>>, int>::type t2;

	BOOST_CHECK((std::is_same<t1, identity<char>>::value));
	BOOST_CHECK((std::is_same<t2, identity<int>>::value));
}

}}}
