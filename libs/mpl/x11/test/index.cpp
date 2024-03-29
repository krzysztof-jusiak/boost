/*=============================================================================
    Copyright (c) 2003      Eric Friedman
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/index.hpp>
#include <boost/mpl/x11/list.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(index_0)
{
	typedef list<int, double, float>::type types;

	typedef index_of<types, int>::type index_of_int;
	typedef index_of<types, double>::type index_of_double;
	typedef index_of<types, float>::type index_of_float;
	typedef index_of<types, char>::type index_of_char;

	BOOST_CHECK_EQUAL((index_of_int::value), 0);
	BOOST_CHECK_EQUAL((index_of_double::value), 1);
	BOOST_CHECK_EQUAL((index_of_float::value), 2);

	BOOST_CHECK((is_void_<index_of_char>::value));
}

}}}
