#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#include <boost/spirit/repository/home/support/unpack_map.hpp>
#include <boost/mpl/x11/map.hpp>
#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/insert.hpp>

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define N_ARG 6

#define T_KEY(z, n, text) struct key##n {};

BOOST_PP_REPEAT(N_ARG, T_KEY, nil)

#define T_VAL(z, n, text) struct val##n { \
void test() { printf("val %d\n", n); }    \
};

BOOST_PP_REPEAT(N_ARG, T_VAL, nil)

namespace x11 = boost::mpl::x11;
namespace repo = boost::spirit::repository;

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

typedef x11::list<key3, key2, key1, key0> key_order;

struct map_apply {
	template <typename...>
	struct apply;

	template <typename T0, typename T1>
	struct apply<x11::package<key1, key0>, T0, T1> {
		typedef x11::list<T1, T0> type;
	};

	template <typename T0, typename T1, typename T2>
	struct apply<x11::package<key2, key1, key0>, T0, T1, T2> {
		typedef x11::list<T2, T1, T0> type;
	};

	template <typename T0, typename T1, typename T2, typename T3>
	struct apply<x11::package<key3, key2, key1, key0>, T0, T1, T2, T3> {
		typedef x11::list<T3, T2, T1, T0> type;
	};
};

template <typename T>
std::string demangle()
{
	auto *s(abi::__cxa_demangle(typeid(T).name(), 0, 0, 0));
	std::string rv(s);
	free(s);
	return rv;
}

int main(int argc, char **argv)
{
	typedef typename x11::apply_wrap<
		repo::unpack_map<map_apply, key_order>, map21_t
	> a21;
	typedef typename x11::apply_wrap<
		repo::unpack_map<map_apply, key_order>, map22_t
	> a22;
	typedef typename x11::apply_wrap<
		repo::unpack_map<map_apply, key_order>, map31_t
	> a31;
	typedef typename x11::apply_wrap<
		repo::unpack_map<map_apply, key_order>, map32_t
	> a32;
	typedef typename x11::apply_wrap<
		repo::unpack_map<map_apply, key_order>, map41_t
	> a41;
	typedef typename x11::apply_wrap<
		repo::unpack_map<map_apply, key_order>, map42_t
	> a42;

	typedef typename x11::insert<map32_t, x11::pair<key3, val3>>::type
	map43_t;
	typedef typename x11::apply_wrap<
		repo::unpack_map<map_apply, key_order>, map43_t
	> a43;
	typedef typename x11::insert<
		typename x11::insert<
			map22_t, x11::pair<key3, val3>
		>::type, x11::pair<key2, val2>
	>::type map44_t;
	typedef typename x11::apply_wrap<
		repo::unpack_map<map_apply, key_order>, map44_t
	> a44;

	std::cout << "a21: " << demangle<typename a21::type>() << '\n';
	std::cout << "a22: " << demangle<typename a22::type>() << '\n';
	std::cout << "a31: " << demangle<typename a31::type>() << '\n';
	std::cout << "a32: " << demangle<typename a32::type>() << '\n';
	std::cout << "a41: " << demangle<typename a41::type>() << '\n';
	std::cout << "a42: " << demangle<typename a42::type>() << '\n';
	std::cout << "a43: " << demangle<typename a43::type>() << '\n';
	std::cout << "a44: " << demangle<typename a44::type>() << '\n';
}
