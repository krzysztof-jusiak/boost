/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/sizeof.hpp>
#include <boost/mpl/x11/arg.hpp>
#include <boost/mpl/x11/logical.hpp>
#include <boost/mpl/x11/comparison.hpp>
#include <boost/mpl/x11/lambda.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace test {
	struct my {
		char a[100];
	};
}

BOOST_AUTO_TEST_CASE(lambda_0)
{
	/* !(x == char) && !(x == double) || sizeof(x) > 8 */
	typedef lambda<or_<
		and_<
			not_<std::is_same<arg<0>, char>>,
			not_<std::is_floating_point<arg<0>>>
		>,
		greater<sizeof_<arg<0>>, size_t<8>>
	>>::type f;

	typedef apply_wrap<f, test::my> x;

	BOOST_CHECK(!(apply_wrap<f, char>::type::value));
	BOOST_CHECK(!(apply_wrap<f, double>::type::value));
	BOOST_CHECK((apply_wrap<f, long>::type::value));
	BOOST_CHECK((apply_wrap<f, test::my>::type::value));
}

BOOST_AUTO_TEST_CASE(lambda_1)
{
	 /* x == y || x == my || sizeof(x) == sizeof(y) */
	typedef lambda<or_<
		std::is_same<arg<0>, arg<1>>,
		std::is_same<arg<1>, test::my>,
		equal_to<sizeof_<arg<0>>, sizeof_<arg<1>>>
	>>::type f;

	BOOST_CHECK(!(apply_wrap<f, double, char>::type::value));
	BOOST_CHECK(!(apply_wrap<f, test::my, int>::type::value));
	BOOST_CHECK(!(apply_wrap<f, test::my, char[99]>::type::value));
	BOOST_CHECK((apply_wrap<f, int, int>::type::value));
	BOOST_CHECK((apply_wrap<f, test::my, test::my>::type::value));
	BOOST_CHECK((apply_wrap<f, signed long, unsigned long>::type::value));
}

BOOST_AUTO_TEST_CASE(lambda_2)
{
	/* bind <-> lambda interaction */
	typedef lambda<less<arg<0>, arg<1>>>::type pred;
	typedef bind<pred, arg<0>, int_<4>> f;

	BOOST_CHECK((apply_wrap<f, int_<3>>::type::value));
}

}}}
