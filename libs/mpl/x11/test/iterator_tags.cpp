/*==============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/iterator_tags.hpp>
#include <boost/mpl/x11/comparison.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(iterator_tags_0)
{
	BOOST_CHECK((less< \
		forward_iterator_tag, bidirectional_iterator_tag \
	>::value));
	BOOST_CHECK((less< \
		bidirectional_iterator_tag, random_access_iterator_tag \
	>::value));
}

}}}
