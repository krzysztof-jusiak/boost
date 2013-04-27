/*==============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/reverse.hpp>
#include <boost/mpl/x11/range_c.hpp>
#include <boost/mpl/x11/equal.hpp>
#include <boost/mpl/x11/list.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(reverse_0)
{
	typedef list_c<int, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0> numbers;
	typedef reverse<numbers>::type result;

	typedef range_c<int, 0, 10> answer;

	BOOST_CHECK((equal<result, answer, equal_to<arg<0>, arg<1>>>::value));
}

}}}
