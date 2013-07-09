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
	numeric_parser<double, precise_real_policy<double>> pdouble;
	double d;

	BOOST_CHECK(test::parse_attr("1.23", pdouble, d));
	BOOST_CHECK_EQUAL(d, 1.23);
#if 0
	d = strtod("1.23e+20", 0);
	BOOST_CHECK_EQUAL(d, 1.23e+20);

	d = strtod("1.23e-20", 0);
	BOOST_CHECK_EQUAL(d, 1.23e-20);

	d = strtod("1.23456789", 0);
	BOOST_CHECK_EQUAL(d, 1.23456789);

	d = strtod("1.23456589e+20", 0);
	BOOST_CHECK_EQUAL(d, 1.23456589e+20);

	d = strtod("1.23e+30", 0);
	BOOST_CHECK_EQUAL(d, 1.23e+30);

	d = strtod("1.23e-30", 0);
	BOOST_CHECK_EQUAL(d, 1.23e-30);

	d = strtod("1.23456789e-20", 0);
	BOOST_CHECK_EQUAL(d, 1.23456789e-20);

	d = strtod("1.23456789e-30", 0);
	BOOST_CHECK_EQUAL(d, 1.23456789e-30);

	d = strtod("1.234567890123456789", 0);
	BOOST_CHECK_EQUAL(d, 1.234567890123456789);

	d = strtod("1.23456789012345678901234567890123456789", 0);
	BOOST_CHECK_EQUAL(d, 1.23456789012345678901234567890123456789);

	d = strtod("1.23e306", 0);
	BOOST_CHECK_EQUAL(d, 1.23e306);

	d = strtod("1.23e-306", 0);
	BOOST_CHECK_EQUAL(d, 1.23e-306);

	d = strtod("1.23e-320", 0);
	BOOST_CHECK_EQUAL(d, 1.23e-320);

	d = strtod("1.23e-20", 0);
	BOOST_CHECK_EQUAL(d, 1.23e-20);

	d = strtod("1.23456789e307", 0);
	BOOST_CHECK_EQUAL(d, 1.23456789e307);

	d = strtod("1.23456589e-307", 0);
	BOOST_CHECK_EQUAL(d, 1.23456589e-307);

	d = strtod("1.234567890123456789", 0);
	BOOST_CHECK_EQUAL(d, 1.234567890123456789);

	d = strtod("1.234567890123456789e301", 0);
	BOOST_CHECK_EQUAL(d, 1.234567890123456789e301);

	d = strtod("1.234567890123456789e-301", 0);
	BOOST_CHECK_EQUAL(d, 1.234567890123456789e-301);

	d = strtod("1.234567890123456789e-321", 0);
	BOOST_CHECK_EQUAL(d, 1.234567890123456789e-321);

	d = strtod("1e23", 0);
	BOOST_CHECK_EQUAL(d, 1e23);
/*
	d = strtod("1e310", 0);
	BOOST_CHECK_EQUAL(d, 1e310);
*/
	d = strtod("9.0259718793241475e-277", 0);
	BOOST_CHECK_EQUAL(d, 9.0259718793241475e-277);

	d = strtod("9.025971879324147880346310405869e-277", 0);
	BOOST_CHECK_EQUAL(d, 9.025971879324147880346310405869e-277);

	d = strtod("9.025971879324147880346310405868e-277", 0);
	BOOST_CHECK_EQUAL(d, 9.025971879324147880346310405868e-277);

	d = strtod("2.2250738585072014e-308", 0);
	BOOST_CHECK_EQUAL(d, 2.2250738585072014e-308);

	d = strtod("2.2250738585072013e-308", 0);
	BOOST_CHECK_EQUAL(d, 2.2250738585072013e-308);
#endif
}

}}}}
