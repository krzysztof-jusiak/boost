/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(if_test)
{
	typedef if_<std::true_type, char, long>::type t1;
	typedef if_c<true, char, long>::type t2;
	typedef if_<std::false_type, char, long>::type t3;
	typedef if_c<false, char, long>::type t4;

	BOOST_CHECK((std::is_same<t1, char>::value));
	BOOST_CHECK((std::is_same<t2, char>::value));
	BOOST_CHECK((std::is_same<t3, long>::value));
	BOOST_CHECK((std::is_same<t4, long>::value));
}

}}}
