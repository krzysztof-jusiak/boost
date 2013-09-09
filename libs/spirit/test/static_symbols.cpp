/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE spirit
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/map.hpp>
#include <boost/mpl/x11/list.hpp>

#include <boost/spirit/home/qi/char/char.hpp>
#include <boost/spirit/repository/home/qi/string/static_symbols.hpp>

#include <boost/math/special_functions/fpclassify.hpp>

#include "test.hpp"

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace test {

typedef mpl::x11::map<
	mpl::x11::pair<
		mpl::x11::list_c<char, 'd', 'o', 'v', 'e'>,
		mpl::x11::int_<354>
	>,
	mpl::x11::pair<
		mpl::x11::list_c<char, 'f', 'i', 'r', 'e'>,
		mpl::x11::int_<124>
	>,
	mpl::x11::pair<
		mpl::x11::list_c<char, 'w', 'i', 'n', 'd'>,
		mpl::x11::int_<423>
	>,
	mpl::x11::pair<
		mpl::x11::list_c<char, 'w', 'a', 't', 'e', 'r'>,
		mpl::x11::int_<765>
	>,
	mpl::x11::pair<
		mpl::x11::list_c<char, 'c', 'l', 'o', 'u', 'd'>,
		mpl::x11::int_<864>
	>,
	mpl::x11::pair<
		mpl::x11::list_c<char, 's', 'e', 'a', 'l'>,
		mpl::x11::int_<999>
	>
> m1;

template <typename T>
struct nan_wrapper {
	typedef T value_type;
	static constexpr T const value = std::numeric_limits<T>::quiet_NaN();
};

template <typename T>
constexpr T const nan_wrapper<T>::value;

template <typename T>
struct inf_wrapper {
	typedef T value_type;
	static constexpr T const value = std::numeric_limits<T>::infinity();
};

template <typename T>
constexpr T const inf_wrapper<T>::value;

typedef mpl::x11::map<
	mpl::x11::pair<
		mpl::x11::list_c<char, 'N', 'a', 'N'>,
		nan_wrapper<double>
	>,
	mpl::x11::pair<
		mpl::x11::list_c<char, 'i', 'n', 'f'>,
		inf_wrapper<double>
	>,
	mpl::x11::pair<
		mpl::x11::list_c<char, 'i', 'n', 'f', 'i', 'n', 'i', 't', 'y'>,
		inf_wrapper<double>
	>,
	mpl::x11::pair<
		mpl::x11::list_c<char, 'n', 'a', 'n', '(', '.', '.', '.', ')'>,
		nan_wrapper<double>
	>
> m2;

}

BOOST_AUTO_TEST_CASE(static_symbols_0)
{
	static_symbols<test::m1> sym;
	int i;

	BOOST_CHECK((test::parse_attr("dove", sym, i)));
	BOOST_CHECK_EQUAL(i, 354);

	BOOST_CHECK((test::parse_attr("fire", sym, i)));
	BOOST_CHECK_EQUAL(i, 124);

	BOOST_CHECK((test::parse_attr("wind", sym, i)));
	BOOST_CHECK_EQUAL(i, 423);

	BOOST_CHECK((test::parse_attr("water", sym, i)));
	BOOST_CHECK_EQUAL(i, 765);

	BOOST_CHECK((test::parse_attr("cloud", sym, i)));
	BOOST_CHECK_EQUAL(i, 864);

	BOOST_CHECK((test::parse_attr("seal", sym, i)));
	BOOST_CHECK_EQUAL(i, 999);

	BOOST_CHECK(!(test::parse_attr("baal", sym, i)));
}

BOOST_AUTO_TEST_CASE(static_symbols_1)
{
	static_symbols<test::m2> sym;
	double d;

	BOOST_CHECK((test::parse_attr("NaN", sym, d)));
	BOOST_CHECK_EQUAL(math::fpclassify(d), FP_NAN);

	BOOST_CHECK((test::parse_attr("inf", sym, d)));
	BOOST_CHECK_EQUAL(math::fpclassify(d), FP_INFINITE);

	BOOST_CHECK((test::parse_attr("nan(...)", sym, d)));
	BOOST_CHECK_EQUAL(math::fpclassify(d), FP_NAN);

	BOOST_CHECK((test::parse_attr("infinity", sym, d)));
	BOOST_CHECK_EQUAL(math::fpclassify(d), FP_INFINITE);
}

}}}}
