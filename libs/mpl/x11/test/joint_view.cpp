/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/joint_view.hpp>
#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/range_c.hpp>
#include <boost/mpl/x11/equal.hpp>
#include <boost/mpl/x11/size.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace test {

template <typename View>
struct is_empty {
	typedef typename begin<View>::type first_;
	typedef typename end<View>::type last_;

	is_empty()
	{
		BOOST_CHECK_EQUAL((size<View>::value), 0);
		BOOST_CHECK((std::is_same<first_, last_>::value));

		BOOST_CHECK((sizeof(View)));
		BOOST_CHECK((sizeof(first_)));
		BOOST_CHECK((sizeof(last_)));
	}
};

}

BOOST_AUTO_TEST_CASE(joint_view_0)
{
	typedef joint_view<range_c<int, 0, 10>, range_c<int, 10, 15>> numbers;

	typedef range_c<int, 0, 15> answer;

	BOOST_CHECK((equal<numbers, answer>::value));
	BOOST_CHECK_EQUAL((size<numbers>::value), 15);
}

BOOST_AUTO_TEST_CASE(joint_view_1)
{
	test::is_empty<joint_view<list<>, list<>>>();
	test::is_empty<joint_view<list<>, joint_view<list<>, list<>>>>();
}

}}}
