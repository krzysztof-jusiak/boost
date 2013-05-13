/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE spirit
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/list.hpp>
#include <boost/spirit/repository/home/qi/string/static_lit.hpp>

#include "test.hpp"

namespace boost { namespace spirit { namespace repository { namespace qi {

BOOST_AUTO_TEST_CASE(static_lit_0)
{
	using boost::mpl::x11::list_c;
	typedef list_c<char, 'a', 'b', 'c', 'd', 'e'> s1;
	typedef list_c<wchar_t, 'a', 'b', 'c', 'd', 'e'> s2;
	typedef list_c<char, 'x'> s3;
	typedef list_c<wchar_t, 'x'> s4;
	
	BOOST_CHECK((test::parse("abcde", static_string<s1>())));
	BOOST_CHECK((test::parse(                                         \
		L"abcde",                                                 \
		static_string<s2, spirit::char_encoding::standard_wide>() \
	)));

	BOOST_CHECK((test::parse("x", static_string<s3>())));
	BOOST_CHECK((test::parse(                                         \
		L"x",                                                     \
		static_string<s4, spirit::char_encoding::standard_wide>() \
	)));
}
#if 0
BOOST_AUTO_TEST_CASE(static_lit_1)
{
        BOOST_CHECK((test("    abcde", static_string<'a', 'b', 'c', 'd', 'e'>(), standard::space)));
        BOOST_CHECK((test(L"    абвгд", string(L"kimpo"), unicode::space)));
        BOOST_CHECK((test("    ы", string('ы'), unicode::space)));
}

BOOST_AUTO_TEST_CASE(static_lit_2)
{
	using namespace boost::spirit::ascii;
        std::string s;
        BOOST_CHECK((test_attr("kimpo", string("kimpo"), s)));
        BOOST_CHECK(s == "kimpo");
        s.clear();
        BOOST_CHECK((test_attr(L"kimpo", string(L"kimpo"), s)));
        BOOST_CHECK(s == "kimpo");
        s.clear();
        BOOST_CHECK((test_attr("x", string("x"), s)));
        BOOST_CHECK(s == "x");
}

BOOST_AUTO_TEST_CASE(static_lit_5)
{
	using namespace boost::spirit::ascii;
        namespace phx = boost::phoenix;

        BOOST_CHECK((test("x", string(phx::val("x")))));

        std::string str; // make sure lazy lits have an attribute
        BOOST_CHECK(test("x", string(phx::val("x"))[phx::ref(str) = _1]));
        BOOST_CHECK(str == "x");
}

BOOST_AUTO_TEST_CASE(static_lit_6)
{
	BOOST_CHECK((test("kimpo", lit("kimpo"))));

        std::basic_string<char> s("kimpo");
        std::basic_string<wchar_t> ws(L"kimpo");
        BOOST_CHECK((test("kimpo", lit(s))));
        BOOST_CHECK((test(L"kimpo", lit(ws))));
}

BOOST_AUTO_TEST_CASE(static_lit_7)
{
	std::basic_string<char> s("kimpo");
        BOOST_CHECK((test("kimpo", lit(s))));

        std::basic_string<wchar_t> ws(L"kimpo");
        BOOST_CHECK((test(L"kimpo", lit(ws))));
}

BOOST_AUTO_TEST_CASE(static_lit_8)
{
	using namespace boost::spirit::ascii;
        BOOST_CHECK((test("    kimpo", lit("kimpo"), space)));
        BOOST_CHECK((test(L"    kimpo", lit(L"kimpo"), space)));
}

BOOST_AUTO_TEST_CASE(static_lit_9)
{
	using namespace boost::spirit::ascii;
        BOOST_CHECK((test("    kimpo", lit("kimpo"), space)));
        BOOST_CHECK((test(L"    kimpo", lit(L"kimpo"), space)));
}
#endif
}}}}