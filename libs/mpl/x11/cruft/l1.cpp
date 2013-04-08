/*=============================================================================
    Copyright (c) 2001-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#include <boost/mpl/x11/sizeof.hpp>
#include <boost/mpl/x11/arg.hpp>
#include <boost/mpl/x11/logical.hpp>
#include <boost/mpl/x11/comparison.hpp>
#include <boost/mpl/x11/lambda.hpp>

template <typename T>
std::string demangle()
{
	auto *s(abi::__cxa_demangle(typeid(T).name(), 0, 0, 0));
	std::string rv(s);
	free(s);
	return rv;
}

namespace boost { namespace mpl { namespace x11 {
namespace test {
	struct my {
		char a[100];
	};
}

void test1()
{
	/* !(x == char) && !(x == double) || sizeof(x) > 8 */
	typedef lambda<or_<
		and_<
			not_<std::is_same<arg<0L>, char>>,
			not_<std::is_floating_point<arg<0L>>>
		>,
		greater<sizeof_<arg<0>>, size_t<8>>
	>> f;

	typedef apply_wrap<f::type, test::my> x;
	std::cout << "1: " << demangle<f>() << '\n';
	std::cout << "2: " << demangle<f::type>() << '\n';
	std::cout << "3: " << demangle<x::type>() << '\n';
	/*
	printf("3: %s\n", typeid(f::x_tag).name());
	printf("4: %s\n", typeid(f::l0::x_tag).name());
	printf("5: %s\n", typeid(f::l0::l0::x_tag).name());
	printf("5.1: %s\n", typeid(f::l0::l0::x_type0).name());
	printf("6.1: %s\n", typeid(f::l0::l0::l0::x_tag).name());
	printf("6.3: %s\n", typeid(f::l0::l0::l1::x_tag).name());
	printf("7: %s\n", typeid(f::l0::l0::l0::result_).name());
*/

}
#if 0
BOOST_AUTO_TEST_CASE(lambda_1)
{
	 /* x == y || x == my || sizeof(x) == sizeof(y) */
	typedef lambda<or_<
		std::is_same<_1, _2>, std::is_same<_2, my>,
		equal_to<sizeof_<_1>, sizeof_<_2>>
	>>::type f;

	BOOST_CHECK(!(apply_wrap<f, double, char>));
	BOOST_CHECK(!(apply_wrap<f, my, int>));
	BOOST_CHECK(!(apply_wrap<f, my, char[99]>));
	BOOST_CHECK((apply_wrap<f, int, int>));
	BOOST_CHECK((apply_wrap<f, my, my>));
	BOOST_CHECK((apply_wrap<f, signed long, unsigned long>));
}

BOOST_AUTO_TEST_CASE(lambda_2)
{
	/* bind <-> lambda interaction */
	typedef lambda<less<_1, _2>>::type pred;
	typedef bind<pred, _1, int_<4>> f;

	BOOST_CHECK((apply_wrap<f, int_<3>>));
}
#endif
}}}

int main(int argc, char **argv)
{
	boost::mpl::x11::test1();
	return 0;
}
