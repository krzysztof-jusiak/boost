/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/detail/largest_int.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(largest_int)
{
	using detail::largest_int;

	BOOST_CHECK((std::is_same<largest_int<bool, bool>::type, bool>::value));
	BOOST_CHECK((std::is_same<largest_int<bool, char>::type, char>::value));
	BOOST_CHECK((std::is_same<largest_int<char, bool>::type, char>::value));
	BOOST_CHECK((std::is_same<largest_int<int, unsigned>::type, unsigned>::value));
	BOOST_CHECK((std::is_same<largest_int<unsigned, long>::type, long>::value));
	BOOST_CHECK((std::is_same<largest_int<bool, char, short, unsigned, long, long long>::type, long long>::value));

}

}}}
