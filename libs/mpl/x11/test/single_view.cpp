/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/single_view.hpp>
#include <boost/mpl/x11/size.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(single_view_0)
{
	typedef single_view<int> view;
	typedef begin<view>::type first;
	typedef end<view>::type last;

	BOOST_CHECK((std::is_same<deref<first>::type, int>::value));
	BOOST_CHECK((std::is_same<next<first>::type, last>::value));
	BOOST_CHECK((std::is_same<prior<last>::type, first>::value));

	BOOST_CHECK((std::is_same<                   \
		advance<first, int_<0>>::type, first \
	>::value));
	BOOST_CHECK((std::is_same<advance<first, int_<1>>::type, last>::value));
	BOOST_CHECK((std::is_same<advance<last, int_<0>>::type, last>::value));
	BOOST_CHECK((std::is_same<                   \
		advance<last, int_<-1>>::type, first \
	>::value));

	BOOST_CHECK_EQUAL((distance<first, first>::value), 0);
	BOOST_CHECK_EQUAL((distance<first, last>::value), 1);
	BOOST_CHECK_EQUAL((distance<last, last>::value), 0);

	BOOST_CHECK_EQUAL((size<view>::value), 1);
}

}}}
