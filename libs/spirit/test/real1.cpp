/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE spirit
#include <boost/test/included/unit_test.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/home/qi/numeric/real.hpp>

#include "test.hpp"

namespace boost { namespace spirit { namespace repository { namespace qi {

BOOST_AUTO_TEST_CASE(real1_0)
{
	double d;

	BOOST_CHECK(test::parse_attr("1.23", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23);

	BOOST_CHECK(test::parse_attr("1.23e+20", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23e+20);

	BOOST_CHECK(test::parse_attr("1.23e-20", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23e-20);

	BOOST_CHECK(test::parse_attr("1.23456789", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23456789);

	BOOST_CHECK(test::parse_attr("1.23456589e+20", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23456589e+20);

	BOOST_CHECK(test::parse_attr("1.23e+30", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23e+30);

	BOOST_CHECK(test::parse_attr("1.23e-30", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23e-30);

	BOOST_CHECK(test::parse_attr("1.23456789e-20", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23456789e-20);

	BOOST_CHECK(test::parse_attr("1.23456789e-30", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23456789e-30);

	BOOST_CHECK(test::parse_attr("1.234567890123456789", double_, d));
	BOOST_CHECK_EQUAL(d, 1.234567890123456789);

	BOOST_CHECK(test::parse_attr("1.23456789012345678901234567890123456789", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23456789012345678901234567890123456789);

	BOOST_CHECK(test::parse_attr("1.23e306", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23e306);

	BOOST_CHECK(test::parse_attr("1.23e-306", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23e-306);

	BOOST_CHECK(test::parse_attr("1.23e-320", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23e-320);

	BOOST_CHECK(test::parse_attr("1.23e-20", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23e-20);

	BOOST_CHECK(test::parse_attr("1.23456789e307", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23456789e307);

	BOOST_CHECK(test::parse_attr("1.23456589e-307", double_, d));
	BOOST_CHECK_EQUAL(d, 1.23456589e-307);

	BOOST_CHECK(test::parse_attr("1.234567890123456789", double_, d));
	BOOST_CHECK_EQUAL(d, 1.234567890123456789);

	BOOST_CHECK(test::parse_attr("1.234567890123456789e301", double_, d));
	BOOST_CHECK_EQUAL(d, 1.234567890123456789e301);

	BOOST_CHECK(test::parse_attr("1.234567890123456789e-301", double_, d));
	BOOST_CHECK_EQUAL(d, 1.234567890123456789e-301);

	BOOST_CHECK(test::parse_attr("1.234567890123456789e-321", double_, d));
	BOOST_CHECK_EQUAL(d, 1.234567890123456789e-321);

	BOOST_CHECK(test::parse_attr("1e23", double_, d));
	BOOST_CHECK_EQUAL(d, 1e23);
/*
	BOOST_CHECK(test::parse_attr("1e310", double_, d));
	BOOST_CHECK_EQUAL(d, 1e310);
*/
#if 0
	BOOST_CHECK(test::parse_attr("9.0259718793241475e-277", double_, d));
	BOOST_CHECK_EQUAL(d, 9.0259718793241475e-277);

	BOOST_CHECK(test::parse_attr("9.025971879324147880346310405869e-277", double_, d));
	BOOST_CHECK_EQUAL(d, 9.025971879324147880346310405869e-277);

	BOOST_CHECK(test::parse_attr("9.025971879324147880346310405868e-277", double_, d));
	BOOST_CHECK_EQUAL(d, 9.025971879324147880346310405868e-277);

	BOOST_CHECK(test::parse_attr("2.2250738585072014e-308", double_, d));
	BOOST_CHECK_EQUAL(d, 2.2250738585072014e-308);

	BOOST_CHECK(test::parse_attr("2.2250738585072013e-308", double_, d));
	BOOST_CHECK_EQUAL(d, 2.2250738585072013e-308);
#endif
}

}}}}
