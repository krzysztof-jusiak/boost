/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/advance.hpp>

namespace boost { namespace mpl { namespace x11 {

namespace test {

template <int pos>
struct iter {
	typedef bidirectional_iterator_tag category;
	typedef iter<(pos + 1)> next;
	typedef iter<(pos - 1)> prior;
	typedef int_<pos> type;
};

typedef iter<0> first;
typedef iter<10> last;

}

BOOST_AUTO_TEST_CASE(advance_0)
{
	typedef x11::advance<test::first, int_<10>>::type iter1;
	typedef advance_c<test::first, 10>::type iter2;

	BOOST_CHECK((std::is_same<iter1, test::last>::value));
	BOOST_CHECK((std::is_same<iter2, test::last>::value));
}

BOOST_AUTO_TEST_CASE(advance_1)
{
	typedef x11::advance<test::last, int_<-10>>::type iter1;
	typedef advance_c<test::last, -10>::type iter2;

	BOOST_CHECK((std::is_same<iter1, test::first>::value));
	BOOST_CHECK((std::is_same<iter2, test::first>::value));
}

}}}
