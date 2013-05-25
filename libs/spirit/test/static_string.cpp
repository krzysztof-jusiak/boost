/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE spirit
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/list.hpp>
#include <boost/spirit/repository/home/qi/string/static_string.hpp>
#include <boost/spirit/home/qi/char.hpp>

#include "test.hpp"

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace test {

typedef mpl::x11::list_c<char, 'a', 'b', 'c', 'd', 'e'> s1;
typedef mpl::x11::list_c<wchar_t, 'a', 'b', 'c', 'd', 'e'> s2;
typedef mpl::x11::list_c<char, 'x'> s3;
typedef mpl::x11::list_c<wchar_t, 'x'> s4;

}

BOOST_AUTO_TEST_CASE(static_string_0)
{
	BOOST_CHECK((test::parse("abcde", static_string<test::s1>())));
	BOOST_CHECK((test::parse(                                      \
		L"abcde", static_string<                               \
			test::s2, spirit::char_encoding::standard_wide \
		>()                                                    \
	)));

	BOOST_CHECK((test::parse("x", static_string<test::s3>())));
	BOOST_CHECK((test::parse(                                      \
		L"x", static_string<                                   \
			test::s4, spirit::char_encoding::standard_wide \
		>()                                                    \
	)));
}

BOOST_AUTO_TEST_CASE(static_string_1)
{
	BOOST_CHECK((test::parse(                                       \
		"    abcde", static_string<test::s1>(), standard::space \
	)));
	BOOST_CHECK((test::parse(                                       \
		L"    abcde", static_string<                            \
			test::s2, spirit::char_encoding::standard_wide  \
		>(), standard_wide::space                               \
	)));
	BOOST_CHECK((test::parse(                                       \
		"    x", static_string<test::s3>(), standard::space     \
	)));
	BOOST_CHECK((test::parse(                                       \
		L"    x", static_string<                                \
			test::s4, spirit::char_encoding::standard_wide  \
		>(), standard_wide::space                               \
	)));
}

BOOST_AUTO_TEST_CASE(static_string_2)
{
	std::string s;
	BOOST_CHECK((test::parse_attr("abcde", static_string<test::s1>(), s)));
	BOOST_CHECK(s == "abcde");

	std::wstring ws;
	BOOST_CHECK((test::parse_attr(                                 \
		L"abcde", static_string<                               \
			test::s2, spirit::char_encoding::standard_wide \
		>(), ws                                                \
	)));
	BOOST_CHECK(ws == L"abcde");

	s.clear();
	BOOST_CHECK((test::parse_attr("x", static_string<test::s3>(), s)));
	BOOST_CHECK(s == "x");

	ws.clear();
	BOOST_CHECK((test::parse_attr(                                 \
		L"x", static_string<                                   \
			test::s4, spirit::char_encoding::standard_wide \
		>(), ws                                                \
	)));
	BOOST_CHECK(ws == L"x");
}

}}}}
