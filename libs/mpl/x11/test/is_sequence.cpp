/*=============================================================================
    Copyright (c) 2002-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/vector.hpp>
#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/range_c.hpp>
#include <boost/mpl/x11/is_sequence.hpp>

#include "data_types.hpp"

namespace boost { namespace mpl { namespace x11 {
namespace test {

template <typename T>
struct std_vector {
	T* begin();
};

}

BOOST_AUTO_TEST_CASE(is_sequence_0)
{
	BOOST_CHECK(!(is_sequence<test::std_vector<int>>::value));
	BOOST_CHECK(!(is_sequence<int_<0> >::value));
	BOOST_CHECK(!(is_sequence<int>::value));
	BOOST_CHECK(!(is_sequence<int &>::value));
	BOOST_CHECK(!(is_sequence<test::UDT>::value));
	BOOST_CHECK(!(is_sequence<test::UDT *>::value));
	BOOST_CHECK((is_sequence<range_c<int, 0, 0>>::value));
	BOOST_CHECK((is_sequence<list<>>::value));
	BOOST_CHECK((is_sequence<list<int>>::value));
	BOOST_CHECK((is_sequence<vector<>>::value));
	BOOST_CHECK((is_sequence<vector<int>>::value));
}

}}}
