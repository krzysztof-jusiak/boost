/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/unique.hpp>
#include <boost/mpl/x11/equal.hpp>
#include <boost/mpl/x11/list.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(unique_0)
{
	typedef list<int, float, float, char, int, int, int, double> types;
	typedef unique<types, std::is_same<arg<0>, arg<1>>>::type result;

	typedef list<int, float, char, int, double>::type answer;
	BOOST_CHECK((equal<result, answer>::value));
}

}}}
