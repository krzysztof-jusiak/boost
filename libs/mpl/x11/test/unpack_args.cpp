/*=============================================================================
    Copyright (c) 2002-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/unpack_args.hpp>
#include <boost/mpl/x11/vector.hpp>

namespace boost { namespace mpl { namespace x11 {

BOOST_AUTO_TEST_CASE(unpack_args_0)
{
	typedef vector<int, int> v2;
	typedef vector<int, char, char, char, int> v5;

	BOOST_CHECK((apply<                                   \
		unpack_args<std::is_same<arg<0>, arg<1>>>, v2 \
	>::type::value));
	BOOST_CHECK((apply<                                   \
		unpack_args<std::is_same<arg<0>, arg<4>>>, v5 \
	>::type::value));
}

}}}
