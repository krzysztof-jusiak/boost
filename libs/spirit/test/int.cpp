/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2011      Bryce Lelbach
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE spirit
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/insert.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/home/qi/numeric/int.hpp>

#include "test.hpp"

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace test {

char const *max_int = "2147483647";
char const *int_overflow = "2147483648";
char const *min_int = "-2147483648";
char const *int_underflow = "-2147483649";

char const *max_long_long = "9223372036854775807";
char const *long_long_overflow = "9223372036854775808";
char const *min_long_long = "-9223372036854775808";
char const *long_long_underflow = "-9223372036854775809";

}

BOOST_AUTO_TEST_CASE(int_0)
{
	int i;

	BOOST_CHECK(test::parse("123456", int_));
	BOOST_CHECK(test::parse_attr("123456", int_, i));
	BOOST_CHECK_EQUAL(i, 123456);

	BOOST_CHECK(test::parse("+123456", int_));
	BOOST_CHECK(test::parse_attr("+123456", int_, i));
	BOOST_CHECK_EQUAL(i, 123456);

	BOOST_CHECK(test::parse("-123456", int_));
	BOOST_CHECK(test::parse_attr("-123456", int_, i));
	BOOST_CHECK_EQUAL(i, -123456);

	BOOST_CHECK(test::parse(test::max_int, int_));
	BOOST_CHECK(test::parse_attr(test::max_int, int_, i));
	BOOST_CHECK_EQUAL(i, INT_MAX);

	BOOST_CHECK(test::parse(test::min_int, int_));
	BOOST_CHECK(test::parse_attr(test::min_int, int_, i));
	BOOST_CHECK_EQUAL(i, INT_MIN);

	BOOST_CHECK(!test::parse(test::int_overflow, int_));
	BOOST_CHECK(!test::parse_attr(test::int_overflow, int_, i));
	BOOST_CHECK(!test::parse(test::int_underflow, int_));
	BOOST_CHECK(!test::parse_attr(test::int_underflow, int_, i));

	BOOST_CHECK(!test::parse("-", int_));
	BOOST_CHECK(!test::parse_attr("-", int_, i));

	BOOST_CHECK(!test::parse("+", int_));
	BOOST_CHECK(!test::parse_attr("+", int_, i));

	/* Bug report from Steve Nutt */
	BOOST_CHECK(!test::parse_attr("5368709120", int_, i));

	/* with leading zeros */
	BOOST_CHECK(test::parse("0000000000123456", int_));
	BOOST_CHECK(test::parse_attr("0000000000123456", int_, i));
	BOOST_CHECK_EQUAL(i, 123456);
}

BOOST_AUTO_TEST_CASE(int_1)
{
	long long ll;
	BOOST_CHECK(test::parse("1234567890123456789", long_long));
	BOOST_CHECK(test::parse_attr("1234567890123456789", long_long, ll));
	BOOST_CHECK_EQUAL(ll, 1234567890123456789LL);

	BOOST_CHECK(test::parse("-1234567890123456789", long_long));
	BOOST_CHECK(test::parse_attr("-1234567890123456789", long_long, ll));
	BOOST_CHECK_EQUAL(ll, -1234567890123456789LL);

	BOOST_CHECK(test::parse(test::max_long_long, long_long));
	BOOST_CHECK(test::parse_attr(test::max_long_long, long_long, ll));
	BOOST_CHECK_EQUAL(ll, LONG_LONG_MAX);

	BOOST_CHECK(test::parse(test::min_long_long, long_long));
	BOOST_CHECK(test::parse_attr(test::min_long_long, long_long, ll));
	BOOST_CHECK_EQUAL(ll, LONG_LONG_MIN);

	BOOST_CHECK(!test::parse(test::long_long_overflow, long_long));
	BOOST_CHECK(!test::parse_attr(test::long_long_overflow, long_long, ll));
	BOOST_CHECK(!test::parse(test::long_long_underflow, long_long));
	BOOST_CHECK(!test::parse_attr(                   \
		test::long_long_underflow, long_long, ll \
	));
}

BOOST_AUTO_TEST_CASE(int_2)
{
	int i;

	BOOST_CHECK(test::parse("12345", short_));
	BOOST_CHECK(test::parse_attr("12345", short_, i));
	BOOST_CHECK_EQUAL(i, 12345);

	BOOST_CHECK(test::parse("1234567890", long_));
	BOOST_CHECK(test::parse_attr("1234567890", long_, i));
	BOOST_CHECK_EQUAL(i, 1234567890);
}

BOOST_AUTO_TEST_CASE(int_3)
{
	int i;

	BOOST_CHECK(test::parse("123456", int_(123456)));
	BOOST_CHECK(!test::parse("123456", int_(654321)));
	BOOST_CHECK(test::parse_attr("123456", int_(123456), i));
	BOOST_CHECK_EQUAL(i, 123456);

	BOOST_CHECK(!test::parse_attr("123456", int_(654321), i));

	BOOST_CHECK(test::parse("+123456", int_(123456)));
	BOOST_CHECK(!test::parse("+123456", int_(654321)));
	BOOST_CHECK(test::parse_attr("+123456", int_(123456), i));
	BOOST_CHECK_EQUAL(i, 123456);
	BOOST_CHECK(!test::parse_attr("+123456", int_(654321), i));

	BOOST_CHECK(test::parse("-123456", int_(-123456)));
	BOOST_CHECK(!test::parse("-123456", int_(123456)));
	BOOST_CHECK(test::parse_attr("-123456", int_(-123456), i));
	BOOST_CHECK_EQUAL(i, -123456);
	BOOST_CHECK(!test::parse_attr("-123456", int_(123456), i));

	BOOST_CHECK(test::parse(test::max_int, int_(INT_MAX)));
	BOOST_CHECK(test::parse_attr(test::max_int, int_(INT_MAX), i));
	BOOST_CHECK_EQUAL(i, INT_MAX);

	BOOST_CHECK(test::parse(test::min_int, int_(INT_MIN)));
	BOOST_CHECK(test::parse_attr(test::min_int, int_(INT_MIN), i));
	BOOST_CHECK_EQUAL(i, INT_MIN);

	BOOST_CHECK(test::parse("0000000000123456", int_(123456)));
	BOOST_CHECK(test::parse_attr("0000000000123456", int_(123456), i));
	BOOST_CHECK_EQUAL(i, 123456);
}

BOOST_AUTO_TEST_CASE(int_4)
{
	int i;

	BOOST_CHECK(test::parse("12345", short_(12345)));
	BOOST_CHECK(!test::parse("12345", short_(54321)));
	BOOST_CHECK(test::parse_attr("12345", short_(12345), i));
	BOOST_CHECK_EQUAL(i, 12345);
	BOOST_CHECK(!test::parse_attr("12345", short_(54321), i));

	BOOST_CHECK(test::parse("1234567890", long_(1234567890L)));
	BOOST_CHECK(!test::parse("1234567890", long_(987654321L)));
	BOOST_CHECK(test::parse_attr("1234567890", long_(1234567890L), i));
	BOOST_CHECK_EQUAL(i, 1234567890);
	BOOST_CHECK(!test::parse_attr("1234567890", long_(987654321L), i));
}

BOOST_AUTO_TEST_CASE(int_5)
{
	long long ll;

	BOOST_CHECK(test::parse(                                              \
		"1234567890123456789", long_long(1234567890123456789LL)       \
	));
	BOOST_CHECK(!test::parse(                                             \
		"1234567890123456789", long_long(0)                           \
	));
	BOOST_CHECK(test::parse_attr(                                         \
		"1234567890123456789", long_long(1234567890123456789LL), ll   \
	));
	BOOST_CHECK_EQUAL(ll, 1234567890123456789LL);
	BOOST_CHECK(!test::parse_attr("1234567890123456789", long_long(0), ll));

	BOOST_CHECK(test::parse(                                              \
		"-1234567890123456789", long_long(-1234567890123456789LL)     \
	));
	BOOST_CHECK(!test::parse(                                             \
		"-1234567890123456789", long_long(1234567890123456789LL)      \
	));
	BOOST_CHECK(test::parse_attr(                                         \
		"-1234567890123456789", long_long(-1234567890123456789LL), ll \
	));
	BOOST_CHECK_EQUAL(ll, -1234567890123456789LL);
	BOOST_CHECK(!test::parse_attr(                                        \
		"-1234567890123456789", long_long(1234567890123456789LL), ll  \
	));

	BOOST_CHECK(test::parse(                                              \
		test::max_long_long, long_long(LONG_LONG_MAX)                 \
	));
	BOOST_CHECK(test::parse_attr(                                         \
		test::max_long_long, long_long(LONG_LONG_MAX), ll             \
	));
	BOOST_CHECK_EQUAL(ll, LONG_LONG_MAX);

	BOOST_CHECK(test::parse(                                              \
		test::min_long_long, long_long(LONG_LONG_MIN)                 \
	));
	BOOST_CHECK(test::parse_attr(                                         \
		test::min_long_long, long_long(LONG_LONG_MIN), ll             \
	));
	BOOST_CHECK_EQUAL(ll, LONG_LONG_MIN);
}

BOOST_AUTO_TEST_CASE(int_6)
{
	using boost::spirit::_1;
	using boost::phoenix::ref;
	using boost::spirit::standard::space;
	int n, m;

	BOOST_CHECK(test::parse("123", int_[ref(n) = _1]));
	BOOST_CHECK_EQUAL(n, 123);
	BOOST_CHECK(test::parse_attr("789", int_[ref(n) = _1], m));
	BOOST_CHECK_EQUAL(n, 789);
	BOOST_CHECK_EQUAL(m, 789);
	BOOST_CHECK(test::parse("   456", int_[ref(n) = _1], space));
	BOOST_CHECK_EQUAL(n, 456);
}

BOOST_AUTO_TEST_CASE(int_7)
{
	using boost::spirit::_1;
	using boost::phoenix::ref;
	using boost::spirit::standard::space;

	int n, m;

	BOOST_CHECK(test::parse("123", int_(123)[ref(n) = _1]));
	BOOST_CHECK_EQUAL(n, 123);
	BOOST_CHECK(!test::parse("123", int_(321)[ref(n) = _1]));

	BOOST_CHECK(test::parse_attr("789", int_(789)[ref(n) = _1], m));
	BOOST_CHECK_EQUAL(n, 789);
	BOOST_CHECK_EQUAL(m, 789);
        BOOST_CHECK(!test::parse_attr("789", int_(987)[ref(n) = _1], m));

        BOOST_CHECK(test::parse("   456", int_(456)[ref(n) = _1], space));
        BOOST_CHECK_EQUAL(n, 456);
        BOOST_CHECK(!test::parse("   456", int_(654)[ref(n) = _1], space));
}

BOOST_AUTO_TEST_CASE(int_8)
{
	using boost::spirit::standard::space;

	int i = 0, j = 0;

	BOOST_CHECK(test::parse_attr("456", int_[_val = _1], i));
	BOOST_CHECK_EQUAL(i, 456);
	BOOST_CHECK(test::parse_attr("   456", int_[_val = _1], j, space));
	BOOST_CHECK_EQUAL(j, 456);
}

BOOST_AUTO_TEST_CASE(int_9)
{
	using boost::phoenix::ref;

	int n = 123, m = 321;

	BOOST_CHECK(test::parse("123", int_(ref(n))));
	BOOST_CHECK(!test::parse("123", int_(ref(m))));
}

BOOST_AUTO_TEST_CASE(int_10)
{
	numeric_parser<int8_t, detail::int_policy<int8_t>> int8_;
	char c;

	BOOST_CHECK(test::parse_attr("99", int8_, c));
	BOOST_CHECK(!test::parse_attr("999", int8_, c));

	int i;
	using boost::spirit::short_;
	BOOST_CHECK(!test::parse_attr("32769", short_, i, false));
	BOOST_CHECK(!test::parse_attr("41234", short_, i, false));
}

BOOST_AUTO_TEST_CASE(int_11)
{
	using boost::spirit::lit;
	int i = 123456;

	BOOST_CHECK( test::parse("123456", lit(_r(123456))));
	BOOST_CHECK(!test::parse("123456", lit(_r(0))));
	BOOST_CHECK( test::parse("123456", lit(_r(i))));
	BOOST_CHECK(!test::parse("123456", lit(_r(-i))));
	BOOST_CHECK( test::parse("+425", lit(_r(425))));
	BOOST_CHECK(!test::parse("+425", lit(_r(17))));
	BOOST_CHECK( test::parse("-2000", lit(_r(-2000))));
	BOOST_CHECK(!test::parse("-2000", lit(_r(2000))));
	BOOST_CHECK( test::parse(test::max_int, lit(_r(INT_MAX))));
	BOOST_CHECK(!test::parse(test::max_int, lit(_r(INT_MIN))));

	BOOST_CHECK( test::parse(test::min_int, lit(_r(INT_MIN))));
	BOOST_CHECK(!test::parse(test::min_int, lit(_r(INT_MAX))));

	BOOST_CHECK(!test::parse("-", lit(_r(8451))));
	BOOST_CHECK(!test::parse("+", lit(_r(8451))));

	BOOST_CHECK(test::parse("000000000098765", lit(_r(98765))));
}

BOOST_AUTO_TEST_CASE(int_12)
{
	using boost::spirit::lit;
	short s = 12345;
	long l = 1234567890L;

	BOOST_CHECK(test::parse("12345", lit(_r(12345))));
	BOOST_CHECK(!test::parse("12345", lit(_r(-12345))));
	BOOST_CHECK(test::parse("12345", lit(_r(s))));
	BOOST_CHECK(!test::parse("12345", lit(_r(-s))));
	BOOST_CHECK(test::parse("-12345", lit(_r(-12345))));
	BOOST_CHECK(!test::parse("-12345", lit(_r(12345))));
	BOOST_CHECK(test::parse("-12345", lit(_r(-s))));
	BOOST_CHECK(!test::parse("-12345", lit(_r(s))));

	BOOST_CHECK(test::parse("1234567890", lit(_r(1234567890))));
	BOOST_CHECK(!test::parse("1234567890", lit(_r(-1234567890))));
	BOOST_CHECK(test::parse("1234567890", lit(_r(l))));
	BOOST_CHECK(!test::parse("1234567890", lit(_r(-l))));
	BOOST_CHECK(test::parse("-1234567890", lit(_r(-1234567890))));
	BOOST_CHECK(!test::parse("-1234567890", lit(_r(1234567890))));
	BOOST_CHECK(test::parse("-1234567890", lit(_r(-l))));
	BOOST_CHECK(!test::parse("-1234567890", lit(_r(l))));
}

BOOST_AUTO_TEST_CASE(int_13)
{
	using boost::spirit::lit;
	long long ll = 1234567890123456789LL;

	BOOST_CHECK(test::parse(                                      \
		"1234567890123456789", lit(_r(1234567890123456789LL)) \
	));
	BOOST_CHECK(!test::parse("1234567890123456789", lit(_r(-19LL))));
	BOOST_CHECK(test::parse("1234567890123456789", lit(_r(ll))));
	BOOST_CHECK(!test::parse("1234567890123456789", lit(_r(-ll))));
	BOOST_CHECK(test::parse(                                \
		"-100000000000000", lit(_r(-100000000000000LL)) \
	));
	BOOST_CHECK(!test::parse("-100000000000000", lit(_r(3243515525263LL))));
	BOOST_CHECK(test::parse(test::max_long_long, lit(_r(LONG_LONG_MAX))));
	BOOST_CHECK(!test::parse(test::max_long_long, lit(_r(LONG_LONG_MIN))));

	BOOST_CHECK(test::parse(test::min_long_long, lit(_r(LONG_LONG_MIN))));
	BOOST_CHECK(!test::parse(test::min_long_long, lit(_r(LONG_LONG_MAX))));
}

BOOST_AUTO_TEST_CASE(int_14)
{
	int i;
	numeric_parser<
		int,
		typename mpl::x11::insert<
			detail::int_policy<int>,
			mpl::x11::pair<
				with_filter, detail::length_filter<2, 4>
			>
		>::type
	> int2;

	BOOST_CHECK(!test::parse("1", int2));
	BOOST_CHECK(test::parse_attr("12", int2, i));
	BOOST_CHECK_EQUAL(i, 12);
	BOOST_CHECK(test::parse_attr("123", int2, i));
	BOOST_CHECK_EQUAL(i, 123);
	BOOST_CHECK(test::parse_attr("1234", int2, i));
	BOOST_CHECK_EQUAL(i, 1234);
	BOOST_CHECK(!test::parse("12345", int2));

	BOOST_CHECK(!test::parse("-1", int2));
	BOOST_CHECK(test::parse_attr("-12", int2, i));
	BOOST_CHECK_EQUAL(i, -12);
	BOOST_CHECK(test::parse_attr("-123", int2, i));
	BOOST_CHECK_EQUAL(i, -123);
	BOOST_CHECK(test::parse_attr("-1234", int2, i));
	BOOST_CHECK_EQUAL(i, -1234);
	BOOST_CHECK(!test::parse("-12345", int2));

}
#if 0

BOOST_AUTO_TEST_CASE(int_15)
{
	using boost::spirit::unused_type;
	numeric_parser<unused_type, detail::int_policy<unused_type>> any_int;

	BOOST_CHECK(test::parse("123456", any_int));
	BOOST_CHECK(test::parse("-123456", any_int));
	BOOST_CHECK(test::parse("-1234567890123456789", any_int));
}

#endif
}}}}