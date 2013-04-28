/*==============================================================================
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2004      Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/pair_view.hpp>
#include <boost/mpl/x11/advance.hpp>
#include <boost/mpl/x11/range_c.hpp>
#include <boost/mpl/x11/vector.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(pair_view_0)
{
	typedef range_c<int, 0, 10> r;
	typedef vector_c<int, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10> v;

	typedef pair_view<r, v> view;
	typedef begin<view>::type first_;
	typedef end<view>::type last_;

	BOOST_CHECK((std::is_same<                           \
		first_::category, random_access_iterator_tag \
	>::value));

	BOOST_CHECK((std::is_same<advance_c<first_, 0>::type, first_>::value));
	BOOST_CHECK((std::is_same<advance_c<last_, 0>::type, last_>::value));
	BOOST_CHECK((std::is_same<advance_c<first_, 10>::type, last_>::value));
	BOOST_CHECK((std::is_same<advance_c<last_, -10>::type, first_>::value));

	typedef advance_c<first_, 5>::type iter;

	BOOST_CHECK((std::is_same<                        \
		deref<iter>::type, pair<int_<5>, int_<4>> \
	>::value));
}

}}}
