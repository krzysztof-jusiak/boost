/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE spirit
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/list.hpp>

#include <boost/spirit/home/qi/char/char.hpp>
#include <boost/spirit/repository/home/qi/string/static_string.hpp>
#include <boost/spirit/repository/home/qi/auxiliary/static_variant.hpp>


#include "test.hpp"

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace test {
	typedef mpl::x11::list_c<char, 'a', 'b', 'c', 'd', 'e'> s1;
	typedef mpl::x11::list_c<char, 'f', 'g', 'h', 'i', 'j'> s2;
	typedef mpl::x11::list_c<char, 'k', 'l', 'm', 'n', 'o'> s3;
	typedef mpl::x11::list_c<char, 'p', 'q', 'r', 's', 't'> s4;
}

BOOST_AUTO_TEST_CASE(static_variant_0)
{
	using mpl::x11::pair;
	using mpl::x11::long_;

	typedef static_variant<
		pair<static_string<test::s1>, long_<0>>,
		pair<static_string<test::s2>, long_<1>>,
		pair<static_string<test::s3>, long_<2>>,
		pair<static_string<test::s4>, long_<3>>
	> p1;

	BOOST_CHECK((test::parse("abcde", p1())));
	BOOST_CHECK((test::parse("fghij", p1())));
	BOOST_CHECK((test::parse("klmno", p1())));
	BOOST_CHECK((test::parse("pqrst", p1())));
	BOOST_CHECK(!(test::parse("uvwxy", p1())));
}

BOOST_AUTO_TEST_CASE(static_variant_1)
{
	using mpl::x11::pair;
	using mpl::x11::long_;

	typedef static_variant<
		pair<static_string<test::s1>, long_<0>>,
		pair<static_string<test::s2>, long_<1>>,
		pair<static_string<test::s3>, long_<2>>,
		pair<static_string<test::s4>, long_<3>>
	> p1;

	BOOST_CHECK((test::parse("  abcde", p1(), standard::space)));
	BOOST_CHECK((test::parse("    fghij", p1(), standard::space)));
	BOOST_CHECK((test::parse(" klmno", p1(), standard::space)));
	BOOST_CHECK((test::parse("pqrst", p1(), standard::space)));
}

BOOST_AUTO_TEST_CASE(static_variant_2)
{
	using mpl::x11::pair;
	using mpl::x11::long_;

	typedef static_variant<
		pair<static_string<test::s1>, long_<0>>,
		pair<static_string<test::s2>, long_<1>>,
		pair<static_string<test::s3>, long_<2>>,
		pair<static_string<test::s4>, long_<3>>
	> p1;

	long v;

	BOOST_CHECK((test::parse_attr("abcde", p1(), v)));
	BOOST_CHECK_EQUAL(v, 0);

	BOOST_CHECK((test::parse_attr("fghij", p1(), v)));
	BOOST_CHECK_EQUAL(v, 1);

	BOOST_CHECK((test::parse_attr("klmno", p1(), v)));
	BOOST_CHECK_EQUAL(v, 2);

	BOOST_CHECK((test::parse_attr("pqrst", p1(), v)));
	BOOST_CHECK_EQUAL(v, 3);
}

}}}}
