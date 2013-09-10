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

#include <boost/math/concepts/real_concept.hpp>
/* boost::math appears to reside in a sort of mess when numeric_limits,
 * copysign and ldexp are concerned.
 */
namespace std {

template <>
struct numeric_limits<boost::math::concepts::real_concept>
: numeric_limits<boost::math::concepts::real_concept_base_type> {};

boost::math::concepts::real_concept copysign(
	boost::math::concepts::real_concept x,
	boost::math::concepts::real_concept y
)
{
	return std::copysign(x.value(), y.value());
}

boost::math::concepts::real_concept ldexp(
	boost::math::concepts::real_concept x, int exp
)
{
	return std::ldexp(x.value(), exp);
}

}

#include <boost/mpl/x11/erase.hpp>
#include <boost/mpl/x11/insert.hpp>
#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/home/qi/numeric/real.hpp>

#include "test.hpp"


namespace boost { namespace spirit { namespace repository { namespace qi {
namespace test {

struct ts_filter {
	boost::any last_good;
	bool first_group;

	template <typename Iterator>
	bool reset(Iterator const &iter)
	{
		last_good = iter;
		first_group = true;
		return true;
	}

	template <typename Iterator>
	bool operator()(Iterator &first, Iterator const &last)
	{
		auto last_iter(boost::any_cast<Iterator>(last_good));
		auto count(first - last_iter);

		switch (count) {
		case 0:
			return false;
		case 1:
		case 2:
			if (!first_group) {
				first = last_iter;
				return false;
			}
			first_group = false;
		case 3:
			if (*first == ',') {
				last_iter += count -1;
				last_good = last_iter;
				++first;
				return true;
			}
		default:
			first = last_iter;
			return false;
		}
	}
};

}

BOOST_AUTO_TEST_CASE(real2_0)
{
	numeric_parser<double, precise_ureal_policy<double>> udouble;
	double d;

	BOOST_CHECK(test::parse("1234", udouble));
	BOOST_CHECK(test::parse_attr("1234", udouble, d));
	BOOST_CHECK_EQUAL(d, 1234);

	BOOST_CHECK(test::parse("1234.5678", udouble));
	BOOST_CHECK(test::parse_attr("1234.5678", udouble, d));
	BOOST_CHECK_EQUAL(d, 1234.5678);

	BOOST_CHECK(test::parse("1.2e3", udouble));
	BOOST_CHECK(test::parse_attr("1.2e3", udouble, d));
	BOOST_CHECK_EQUAL(d, 1.2e3);

	BOOST_CHECK(test::parse("1.2e-3", udouble));
	BOOST_CHECK(test::parse_attr("1.2e-3", udouble, d));
	BOOST_CHECK_EQUAL(d, 1.2e-3);

	BOOST_CHECK(test::parse("1.e2", udouble));
	BOOST_CHECK(test::parse_attr("1.e2", udouble, d));
	BOOST_CHECK_EQUAL(d, 1.e2);

	BOOST_CHECK(test::parse("1.", udouble));
	BOOST_CHECK(test::parse_attr("1.", udouble, d));
	BOOST_CHECK_EQUAL(d, 1.);
	BOOST_CHECK(test::parse(".2e3", udouble));
	BOOST_CHECK(test::parse_attr(".2e3", udouble, d));
	BOOST_CHECK_EQUAL(d, .2e3);

	BOOST_CHECK(test::parse("2e3", udouble));
	BOOST_CHECK(test::parse_attr("2e3", udouble, d));
	BOOST_CHECK_EQUAL(d, 2e3);

	BOOST_CHECK(test::parse("2", udouble));
	BOOST_CHECK(test::parse_attr("2", udouble, d));
	BOOST_CHECK_EQUAL(d, 2);

	using boost::math::fpclassify;
	BOOST_CHECK(test::parse("inf", udouble));
	BOOST_CHECK(test::parse("infinity", udouble));
	BOOST_CHECK(test::parse("INF", udouble));
	BOOST_CHECK(test::parse("INFINITY", udouble));
	BOOST_CHECK(test::parse_attr("inf", udouble, d));
	BOOST_CHECK_EQUAL(FP_INFINITE, fpclassify(d));
	BOOST_CHECK(test::parse_attr("INF", udouble, d));
	BOOST_CHECK_EQUAL(FP_INFINITE, fpclassify(d));
	BOOST_CHECK(test::parse_attr("infinity", udouble, d));
	BOOST_CHECK_EQUAL(FP_INFINITE, fpclassify(d));
	BOOST_CHECK(test::parse_attr("INFINITY", udouble, d));
	BOOST_CHECK_EQUAL(FP_INFINITE, fpclassify(d));

	BOOST_CHECK(test::parse("nan", udouble));
	BOOST_CHECK(test::parse_attr("nan", udouble, d));
	BOOST_CHECK_EQUAL(FP_NAN, fpclassify(d));
	BOOST_CHECK(test::parse("NAN", udouble));
	BOOST_CHECK(test::parse_attr("NAN", udouble, d));
	BOOST_CHECK_EQUAL(FP_NAN, fpclassify(d));
	BOOST_CHECK(test::parse("nan(...)", udouble));
	BOOST_CHECK(test::parse_attr("nan(...)", udouble, d));
	BOOST_CHECK_EQUAL(FP_NAN, fpclassify(d));
	BOOST_CHECK(test::parse("NAN(...)", udouble));
	BOOST_CHECK(test::parse_attr("NAN(...)", udouble, d));
	BOOST_CHECK_EQUAL(FP_NAN, fpclassify(d));

	BOOST_CHECK(!test::parse("e3", udouble));
	BOOST_CHECK(!test::parse_attr("e3", udouble, d));

	BOOST_CHECK(!test::parse("-1.2e3", udouble));
	BOOST_CHECK(!test::parse_attr("-1.2e3", udouble, d));

	BOOST_CHECK(!test::parse("+1.2e3", udouble));
	BOOST_CHECK(!test::parse_attr("+1.2e3", udouble, d));

	BOOST_CHECK(!test::parse("1.2e", udouble));
	BOOST_CHECK(!test::parse_attr("1.2e", udouble, d));

	BOOST_CHECK(!test::parse("-.3", udouble));
	BOOST_CHECK(!test::parse_attr("-.3", udouble, d));
}

BOOST_AUTO_TEST_CASE(real2_1)
{
	double d;

	BOOST_CHECK(test::parse("-1234", double_));
	BOOST_CHECK(test::parse_attr("-1234", double_, d));
	BOOST_CHECK_EQUAL(d, -1234);

	BOOST_CHECK(test::parse("+1234.5678", double_));
	BOOST_CHECK(test::parse_attr("+1234.5678", double_, d));
	BOOST_CHECK_EQUAL(d, 1234.5678);

	BOOST_CHECK(test::parse("-1234.5678", double_));
	BOOST_CHECK(test::parse_attr("-1234.5678", double_, d));
	BOOST_CHECK_EQUAL(d, -1234.5678);

	BOOST_CHECK(test::parse("-1.2e3", double_));
	BOOST_CHECK(test::parse_attr("-1.2e3", double_, d));
	BOOST_CHECK_EQUAL(d, -1.2e3);

	BOOST_CHECK(test::parse("+1.2e3", double_));
	BOOST_CHECK(test::parse_attr("+1.2e3", double_, d));
	BOOST_CHECK_EQUAL(d, 1.2e3);

	BOOST_CHECK(test::parse("-0.1", double_));
	BOOST_CHECK(test::parse_attr("-0.1", double_, d));
	BOOST_CHECK_EQUAL(d, -0.1);

	BOOST_CHECK(test::parse("-1.2e-3", double_));
	BOOST_CHECK(test::parse_attr("-1.2e-3", double_, d));
	BOOST_CHECK_EQUAL(d, -1.2e-3);

	BOOST_CHECK(test::parse("-1.e2", double_));
	BOOST_CHECK(test::parse_attr("-1.e2", double_, d));
	BOOST_CHECK_EQUAL(d, -1.e2);

	BOOST_CHECK(test::parse("-.2e3", double_));
	BOOST_CHECK(test::parse_attr("-.2e3", double_, d));
	BOOST_CHECK_EQUAL(d, -.2e3);

	BOOST_CHECK(test::parse("-2e3", double_));
	BOOST_CHECK(test::parse_attr("-2e3", double_, d));
	BOOST_CHECK_EQUAL(d, -2e3);

	BOOST_CHECK(!test::parse("-e3", double_));
	BOOST_CHECK(!test::parse_attr("-e3", double_, d));

	BOOST_CHECK(!test::parse("-1.2e", double_));
	BOOST_CHECK(!test::parse_attr("-1.2e", double_, d));

	BOOST_CHECK(test::parse_attr("-5.7222349715140557", double_, d));
	BOOST_CHECK_EQUAL(d, -5.7222349715140557);

	BOOST_CHECK(test::parse_attr("2.0332938517515416", double_, d));
	BOOST_CHECK_EQUAL(d, 2.0332938517515416);

	BOOST_CHECK(test::parse_attr("-5.7222349715140557e+307", double_, d));
	BOOST_CHECK_EQUAL(d, -5.7222349715140557e+307);

	BOOST_CHECK(test::parse_attr("2.0332938517515416e-308", double_, d));
	BOOST_CHECK_EQUAL(d, 2.0332938517515416e-308);

	BOOST_CHECK(test::parse_attr("20332938517515416e291", double_, d));
	BOOST_CHECK_EQUAL(d, 20332938517515416e291);

	BOOST_CHECK(test::parse_attr("2.0332938517515416e307", double_, d));
	BOOST_CHECK_EQUAL(d, 2.0332938517515416e307);

	using boost::math::fpclassify;
	using boost::spirit::detail::signbit;

	BOOST_CHECK(test::parse("-inf", double_));
	BOOST_CHECK(test::parse("-infinity", double_));

	BOOST_CHECK(test::parse_attr("-inf", double_, d));
	BOOST_CHECK_EQUAL(FP_INFINITE, fpclassify(d));
	BOOST_CHECK(signbit(d));

	BOOST_CHECK(test::parse_attr("-infinity", double_, d));
	BOOST_CHECK_EQUAL(FP_INFINITE, fpclassify(d));
	BOOST_CHECK(signbit(d));

	BOOST_CHECK(test::parse("-INF", double_));
	BOOST_CHECK(test::parse("-INFINITY", double_));
	BOOST_CHECK(test::parse_attr("-INF", double_, d));
	BOOST_CHECK_EQUAL(FP_INFINITE, fpclassify(d));
	BOOST_CHECK(signbit(d));

	BOOST_CHECK(test::parse_attr("-INFINITY", double_, d));
	BOOST_CHECK_EQUAL(FP_INFINITE, fpclassify(d));
	BOOST_CHECK(signbit(d));

	BOOST_CHECK(test::parse("-nan", double_));
	BOOST_CHECK(test::parse_attr("-nan", double_, d));
	BOOST_CHECK_EQUAL(FP_NAN, fpclassify(d));
	BOOST_CHECK(signbit(d));

	BOOST_CHECK(test::parse("-NAN", double_));
	BOOST_CHECK(test::parse_attr("-NAN", double_, d));
	BOOST_CHECK_EQUAL(FP_NAN, fpclassify(d));
	BOOST_CHECK(signbit(d));

	BOOST_CHECK(test::parse("-nan(...)", double_));
	BOOST_CHECK(test::parse_attr("-nan(...)", double_, d));
	BOOST_CHECK_EQUAL(FP_NAN, fpclassify(d));
	BOOST_CHECK(signbit(d));

	BOOST_CHECK(test::parse("-NAN(...)", double_));
	BOOST_CHECK(test::parse_attr("-NAN(...)", double_, d));
	BOOST_CHECK_EQUAL(FP_NAN, fpclassify(d));
	BOOST_CHECK(signbit(d));
}

BOOST_AUTO_TEST_CASE(real2_2)
{
	numeric_parser<double, precise_ureal_policy<double>> udouble;
	double d;

	BOOST_CHECK(test::parse("1234", udouble(1234)));
	BOOST_CHECK(!test::parse("1234", udouble(4321)));
	BOOST_CHECK(test::parse_attr("1234", udouble(1234), d));
	BOOST_CHECK_EQUAL(d, 1234);
	BOOST_CHECK(!test::parse_attr("1234", udouble(4321), d));

	BOOST_CHECK(test::parse("1.2e3", udouble(1.2e3)));
	BOOST_CHECK(!test::parse("1.2e3", udouble(3.2e1)));
	BOOST_CHECK(test::parse_attr("1.2e3", udouble(1.2e3), d));
	BOOST_CHECK_EQUAL(d, 1.2e3);
	BOOST_CHECK(!test::parse_attr("1.2e3", udouble(3.2e1), d));
}

BOOST_AUTO_TEST_CASE(real2_3)
{
	double d;

	BOOST_CHECK(test::parse("+1234", double_(1234)));
	BOOST_CHECK(!test::parse("+1234", double_(-1234)));
	BOOST_CHECK(test::parse_attr("+1234", double_(1234), d));
	BOOST_CHECK_EQUAL(d, 1234);
	BOOST_CHECK(!test::parse_attr("+1234", double_(-1234), d));

	BOOST_CHECK(test::parse("-1234", double_(-1234)));
	BOOST_CHECK(!test::parse("-1234", double_(1234)));
	BOOST_CHECK(test::parse_attr("-1234", double_(-1234), d));
	BOOST_CHECK_EQUAL(d, -1234);
	BOOST_CHECK(!test::parse_attr("-1234", double_(1234), d));

	BOOST_CHECK(test::parse("+1.2e3", double_(1.2e3)));
	BOOST_CHECK(!test::parse("+1.2e3", double_(-1.2e3)));
	BOOST_CHECK(test::parse_attr("+1.2e3", double_(1.2e3), d));
	BOOST_CHECK_EQUAL(d, 1.2e3);
	BOOST_CHECK(!test::parse_attr("+1.2e3", double_(-1.2e3), d));

	BOOST_CHECK(test::parse("-1.2e3", double_(-1.2e3)));
	BOOST_CHECK(!test::parse("-1.2e3", double_(1.2e3)));
	BOOST_CHECK(test::parse_attr("-1.2e3", double_(-1.2e3), d));
	BOOST_CHECK_EQUAL(d, -1.2e3);
	BOOST_CHECK(!test::parse_attr("-1.2e3", double_(1.2e3), d));
}

BOOST_AUTO_TEST_CASE(real2_4)
{
	BOOST_CHECK(test::parse("+1.2e3", lit(_r(1.2e3))));
	BOOST_CHECK(!test::parse("+1.2e3", lit(_r(-1.2e3))));
	BOOST_CHECK(test::parse("-1.2e3", lit(_r(-1.2e3))));
	BOOST_CHECK(!test::parse("-1.2e3", lit(_r(1.2e3))));
	BOOST_CHECK(test::parse("1.2e3", lit(_r(1.2e3))));
	BOOST_CHECK(!test::parse("1.2e3", lit(_r(3.2e1))));
}

BOOST_AUTO_TEST_CASE(real2_5)
{
	using math::concepts::real_concept;
	using math::concepts::real_concept_base_type;

	numeric_parser<
		real_concept, precise_real_policy<real_concept>
	> custom_real;
	real_concept d;

	BOOST_CHECK(test::parse("-1234", custom_real));
	BOOST_CHECK(test::parse_attr("-1234", custom_real, d));
	BOOST_CHECK_EQUAL(d, -1234);

	BOOST_CHECK(test::parse("1234.4567", custom_real));
	BOOST_CHECK(test::parse_attr("1234.4567", custom_real, d));
#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
	BOOST_CHECK_EQUAL(d, 1234.4567);
#else
	BOOST_CHECK_EQUAL(d, 1234.4567L);
#endif

	BOOST_CHECK(test::parse("-1.2e3", custom_real));
	BOOST_CHECK(test::parse_attr("-1.2e3", custom_real, d));
	BOOST_CHECK_EQUAL(d, -1.2e3);

	BOOST_CHECK(test::parse("+1.2e3", custom_real));
	BOOST_CHECK(test::parse_attr("+1.2e3", custom_real, d));
	BOOST_CHECK_EQUAL(d, 1.2e3);

	BOOST_CHECK(test::parse("-0.1", custom_real));
	BOOST_CHECK(test::parse_attr("-0.1", custom_real, d));
#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
	BOOST_CHECK_EQUAL(d, -0.1);
#else
	BOOST_CHECK_EQUAL(d, -0.1L);
#endif

	BOOST_CHECK(test::parse("-1.2e-3", custom_real));
	BOOST_CHECK(test::parse_attr("-1.2e-3", custom_real, d));
#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
	BOOST_CHECK_EQUAL(d, -1.2e-3);
#else
	BOOST_CHECK_EQUAL(d, -1.2e-3L);
#endif

	BOOST_CHECK(test::parse("-1.e2", custom_real));
	BOOST_CHECK(test::parse_attr("-1.e2", custom_real, d));
	BOOST_CHECK_EQUAL(d, -1.e2);

	BOOST_CHECK(test::parse("-.2e3", custom_real));
	BOOST_CHECK(test::parse_attr("-.2e3", custom_real, d));
	BOOST_CHECK_EQUAL(d, -.2e3);

	BOOST_CHECK(test::parse("-2e3", custom_real));
	BOOST_CHECK(test::parse_attr("-2e3", custom_real, d));
	BOOST_CHECK_EQUAL(d, -2e3);

	BOOST_CHECK(!test::parse("-e3", custom_real));
	BOOST_CHECK(!test::parse_attr("-e3", custom_real, d));

	BOOST_CHECK(!test::parse("-1.2e", custom_real));
	BOOST_CHECK(!test::parse_attr("-1.2e", custom_real, d));
}

BOOST_AUTO_TEST_CASE(real2_6)
{
	using math::concepts::real_concept;
	numeric_parser<
		real_concept, precise_real_policy<real_concept>
	> custom_real;
	real_concept d;

	BOOST_CHECK(test::parse("-1234", custom_real(-1234)));
	BOOST_CHECK(!test::parse("-1234", custom_real(4321)));
	BOOST_CHECK(test::parse_attr("-1234", custom_real(-1234), d));
	BOOST_CHECK_EQUAL(d, -1234);
	BOOST_CHECK(!test::parse_attr("-1234", custom_real(-4321), d));

	BOOST_CHECK(test::parse("1.2e3", custom_real(1.2e3)));
	BOOST_CHECK(!test::parse("1.2e3", custom_real(-1.2e3)));
	BOOST_CHECK(test::parse_attr("1.2e3", custom_real(1.2e3), d));
	BOOST_CHECK_EQUAL(d, 1.2e3);
	BOOST_CHECK(!test::parse_attr("1.2e3", custom_real(-3.2e1), d));
}

BOOST_AUTO_TEST_CASE(real2_7)
{
	numeric_parser<
		double, precise_ureal_policy<double>,
		mpl::x11::set<flag::expect_dot>
	> strict_udouble;
	numeric_parser<
		double, precise_real_policy<double>,
		mpl::x11::set<flag::expect_dot>
	> strict_double;

	double d;

	BOOST_CHECK(!test::parse("1234", strict_udouble));
	BOOST_CHECK(!test::parse_attr("1234", strict_udouble, d));

	BOOST_CHECK(test::parse("1.2", strict_udouble));
	BOOST_CHECK(test::parse_attr("1.2", strict_udouble, d));
	BOOST_CHECK_EQUAL(d, 1.2);

	BOOST_CHECK(!test::parse("-1234", strict_double));
	BOOST_CHECK(!test::parse_attr("-1234", strict_double, d));

	BOOST_CHECK(test::parse("123.", strict_double));
	BOOST_CHECK(test::parse_attr("123.", strict_double, d));
	BOOST_CHECK_EQUAL(d, 123);

	BOOST_CHECK(test::parse("3.E6", strict_double));
	BOOST_CHECK(test::parse_attr("3.E6", strict_double, d));
	BOOST_CHECK_EQUAL(d, 3e6);

	numeric_parser<
		double, precise_real_policy<double>,
		mpl::x11::set<flag::no_trailing_dot>
	> notrdot_real;

	numeric_parser<
		double, precise_real_policy<double>,
		mpl::x11::set<flag::no_leading_dot>
	> nolddot_real;

	BOOST_CHECK(!test::parse("1234.", notrdot_real));
	BOOST_CHECK(!test::parse(".1234", nolddot_real));
}

BOOST_AUTO_TEST_CASE(real2_8)
{
	typedef typename mpl::x11::insert<
		typename mpl::x11::erase_key<
			typename mpl::x11::erase_key<
				typename mpl::x11::erase_key<
					precise_real_policy<double>,
					with_special
				>::type, with_exponent_sign
			>::type, with_exponent
		>::type, mpl::x11::pair<with_filter, test::ts_filter>
	>::type ts_policy;

	numeric_parser<double, ts_policy> ts_real;
	double  d;

	BOOST_CHECK(test::parse("123,456,789.01", ts_real));
	BOOST_CHECK(test::parse_attr("123,456,789.01", ts_real, d));
	BOOST_CHECK_EQUAL(d, 123456789.01);

	BOOST_CHECK(test::parse("12,345,678.90", ts_real));
	BOOST_CHECK(test::parse_attr("12,345,678.90", ts_real, d));
	BOOST_CHECK_EQUAL(d, 12345678.90);

	BOOST_CHECK(test::parse("1,234,567.89", ts_real));
	BOOST_CHECK(test::parse_attr("1,234,567.89", ts_real, d));
	BOOST_CHECK_EQUAL(d, 1234567.89);

	BOOST_CHECK(!test::parse("1234,567,890", ts_real));
	BOOST_CHECK(!test::parse("1,234,5678,9", ts_real));
	BOOST_CHECK(!test::parse("1,234,567.89e6", ts_real));
	BOOST_CHECK(!test::parse("1,66", ts_real));
}

}}}}
