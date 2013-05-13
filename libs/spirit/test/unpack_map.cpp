/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE spirit
#include <boost/test/included/unit_test.hpp>

#include <boost/spirit/repository/home/support/unpack_map.hpp>
#include <boost/mpl/x11/insert.hpp>
#include <boost/mpl/x11/erase.hpp>
#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/map.hpp>

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace spirit { namespace repository {

namespace x11 = boost::mpl::x11;

namespace test {

#define N_ARG 6

#define T_KEY(z, n, text) struct key##n { typedef x11::long_<n> ord; };

BOOST_PP_REPEAT(N_ARG, T_KEY, nil)

#define T_VAL(z, n, text) struct val##n { \
void test() { typedef x11::long_<n> type; }    \
};

BOOST_PP_REPEAT(N_ARG, T_VAL, nil)

#define T_KEY_DEF(z, n, text) key##n

typedef x11::list<BOOST_PP_ENUM(N_ARG, T_KEY_DEF, nil)> key_order;

typedef x11::map<x11::pair<key0, val0>, x11::pair<key1, val1>> map21_t;
typedef x11::map<x11::pair<key1, val1>, x11::pair<key0, val0>> map22_t;

typedef x11::map<
	x11::pair<key0, val0>,
	x11::pair<key1, val1>,
	x11::pair<key2, val2>
> map31_t;

typedef x11::map<
	x11::pair<key2, val2>,
	x11::pair<key0, val0>,
	x11::pair<key1, val1>
> map32_t;

typedef x11::map<
	x11::pair<key3, val3>,
	x11::pair<key0, val0>,
	x11::pair<key1, val1>,
	x11::pair<key2, val2>
> map41_t;

typedef x11::map<
	x11::pair<key2, val2>,
	x11::pair<key0, val0>,
	x11::pair<key3, val3>,
	x11::pair<key1, val1>
> map42_t;

struct map_apply {
	template <typename...>
	struct apply;

	template <typename T0, typename T1>
	struct apply<x11::package<key0, key1>, T0, T1> {
		typedef x11::list<T0, T1> type;
	};

	template <typename T0, typename T1, typename T2>
	struct apply<x11::package<key0, key1, key2>, T0, T1, T2> {
		typedef x11::list<T0, T1, T2> type;
	};

	template <typename T0, typename T1, typename T2, typename T3>
	struct apply<x11::package<key0, key1, key2, key3>, T0, T1, T2, T3> {
		typedef x11::list<T0, T1, T2, T3> type;
	};
};

}

BOOST_AUTO_TEST_CASE(unpack_map_0)
{
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, test::map21_t
	>::type a21;
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, test::map22_t
	>::type a22;
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, test::map31_t
	>::type a31;
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, test::map32_t
	>::type a32;
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, test::map41_t
	>::type a41;
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, test::map42_t
	>::type a42;

	BOOST_CHECK((std::is_same<a21, a22>::value));
	BOOST_CHECK((std::is_same<a31, a32>::value));
	BOOST_CHECK((std::is_same<a41, a42>::value));
}

BOOST_AUTO_TEST_CASE(unpack_map_1)
{
	typedef typename x11::erase_key<
		typename x11::erase_key<test::map42_t, test::key2>::type,
		test::key3
	>::type map23_t;
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, test::map21_t
	>::type a21;
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, map23_t
	>::type a23;

	BOOST_CHECK((std::is_same<a21, a23>::value));

	typedef typename x11::insert<
		typename x11::insert<
			test::map22_t, x11::pair<test::key3, test::val3>
		>::type, x11::pair<test::key2, test::val2>
	>::type map43_t;
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, test::map42_t
	>::type a42;
	typedef typename x11::apply_wrap<
		unpack_map<test::map_apply, test::key_order>, map43_t
	>::type a43;

	BOOST_CHECK((std::is_same<a42, a43>::value));
}

}}}
