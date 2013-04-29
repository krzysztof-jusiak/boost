/*==============================================================================
    Copyright (c) 2003-2006 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE mpl
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/x11/multiset.hpp>

#include "data_types.hpp"

namespace boost { namespace mpl { namespace x11 {
namespace test {

struct data1 {
	typedef multiset<> s0;
	typedef multiset<int> s1;
	typedef multiset<int, char &> s2;
	typedef multiset<int, char &, int> s3;
	typedef multiset<int, char &, int, abstract> s4;
};

struct data2 {
	typedef multiset<> s0;
	typedef multiset<int> s1;
	typedef multiset<int, char &> s2;
	typedef multiset<int, char &, int> s3;
	typedef multiset<int, char &, int, abstract> s4;
};

template <typename S0>
struct data {
	typedef S0 s0;
	typedef typename insert<s0, int>::type s1;
	typedef typename insert<s1, char&>::type s2;
	typedef typename insert<s2, int>::type s3;
	typedef typename insert<s3, abstract>::type s4;
};

template <typename T>
void count_test()
{
	BOOST_CHECK_EQUAL((count<typename T::s0, int>::value), 0);
	BOOST_CHECK_EQUAL((count<typename T::s1, int>::value), 1);
	BOOST_CHECK_EQUAL((count<typename T::s2, int>::value), 1);
	BOOST_CHECK_EQUAL((count<typename T::s2, char &>::value), 1);
	BOOST_CHECK_EQUAL((count<typename T::s3, int>::value), 2);
	BOOST_CHECK_EQUAL((count<typename T::s3, char &>::value), 1);
	BOOST_CHECK_EQUAL((count<typename T::s4, abstract>::value), 1);
}

template <typename T>
void find_test()
{
	BOOST_CHECK_EQUAL((size<T>::value), 3);

	typedef typename end<T>::type not_found;
	BOOST_CHECK(!(std::is_same<                       \
		typename find<T, int>::type, not_found    \
	>::value));
	BOOST_CHECK(!(std::is_same<                       \
		typename find<T, long>::type, not_found   \
	>::value));
	BOOST_CHECK(!(std::is_same<                       \
		typename find<T, char>::type, not_found   \
	>::value));
	BOOST_CHECK((std::is_same<                        \
		typename find<T, char *>::type, not_found \
	>::value));
}

}

BOOST_AUTO_TEST_CASE(multiset_0)
{
	count_test<test::data1>();
	count_test<test::data<multiset<>>>();
}

BOOST_AUTO_TEST_CASE(multiset_1)
{
	typedef insert<multiset<>, int>::type set_of_1_int;
	typedef begin<set_of_1_int>::type iter_to_1_int;
	BOOST_CHECK((std::is_same<deref<iter_to_1_int>::type, int>::value));

	typedef multiset<> s0;
	typedef insert<s0, int>::type s1;
	typedef insert<s1, long>::type s2;
	typedef insert<s2, char>::type myset;

	find_test<myset>();
	find_test<myset::type>();
}

}}}
