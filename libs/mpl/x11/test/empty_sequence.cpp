/*=============================================================================
    Copyright (c) 2004      Aleksey Gurtovoy
    Copyright (c) 2004      Alexander Nasonov
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/empty_sequence.hpp>
#include <boost/mpl/x11/size.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(empty_sequence_0)
{
	typedef begin<empty_sequence>::type begin;
	typedef end<empty_sequence>::type end;

	BOOST_CHECK((std::is_same<begin, end>::value));
	BOOST_CHECK_EQUAL((distance<begin, end>::value), 0);
	BOOST_CHECK_EQUAL((size<empty_sequence>::value), 0);

	typedef advance_c<begin, 0>::type advanced;
	BOOST_CHECK((std::is_same<advanced, end>::value));
}

}}}
