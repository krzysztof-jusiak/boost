/*=============================================================================
    Copyright (c) 2003      Eric Friedman
    Copyright (c) 2004      Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/stable_partition.hpp>
#include <boost/mpl/x11/comparison.hpp>
#include <boost/mpl/x11/vector.hpp>
#include <boost/mpl/x11/equal.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace test {

typedef vector_c<int, 3, 4, 0, -5, 8, -1, 7>::type numbers;
typedef vector_c<int, 0, -5, -1>::type manual_first;
typedef vector_c<int, 3, 4, 8, 7>::type manual_second;

}

BOOST_AUTO_TEST_CASE(stable_partition_0)
{
	typedef stable_partition<
		test::numbers, less<arg<-1>, int_<3>>
	>::type result;

	BOOST_CHECK((equal<result::first, test::manual_first>::value));
	BOOST_CHECK((equal<result::second, test::manual_second>::value));
}

BOOST_AUTO_TEST_CASE(stable_partition_1)
{
	typedef stable_partition<
		test::numbers, greater_equal<arg<-1>, int_<3>>
	>::type result;

	BOOST_CHECK((equal<result::first, test::manual_second>::value));
	BOOST_CHECK((equal<result::second, test::manual_first>::value));
}

}}}
