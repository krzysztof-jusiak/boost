/*==============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/min_max.hpp>
#include <boost/mpl/x11/integral.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(min_max_0)
{

	BOOST_CHECK((std::is_same<                      \
		min<int_<5>, int_<7>>::type, int_<5>    \
	>::value));
	BOOST_CHECK((std::is_same<                      \
		max<int_<5>, int_<7>>::type, int_<7>    \
	>::value));
	BOOST_CHECK((std::is_same<                      \
		min<int_<-5>, int_<-7>>::type, int_<-7> \
	>::value));
	BOOST_CHECK((std::is_same<                      \
		max<int_<-5>, int_<-7>>::type, int_<-5> \
	>::value));
}

}}}
