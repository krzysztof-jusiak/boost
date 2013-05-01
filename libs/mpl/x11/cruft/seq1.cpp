
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#include <boost/mpl/x11/at.hpp>
#include <boost/mpl/x11/map.hpp>
#include <boost/mpl/x11/list.hpp>
#include <boost/mpl/x11/erase.hpp>
#include <boost/mpl/x11/vector.hpp>
#include <boost/mpl/x11/transform.hpp>
#include <boost/mpl/x11/unpack_args.hpp>

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace x11 = boost::mpl::x11;

#define N_ARG 4

#define T_KEY(z, n, text) struct key##n {};

BOOST_PP_REPEAT(N_ARG, T_KEY, nil)

#define T_VAL(z, n, text) struct val##n { \
void test() { printf("val %d\n", n); }    \
};

BOOST_PP_REPEAT(N_ARG, T_VAL, nil)

#define T_MAP_PAIR(z, n, text) x11::pair<key##n, val##n>

#define T_MAP(z, n, text) typedef x11::map< \
BOOST_PP_ENUM_ ## z(n, T_MAP_PAIR, nil)     \
> map##n##_t;

BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(N_ARG), T_MAP, nil)
/*
template <typename...>
struct Sx;

template <>
struct Sx<> {
	template <typename T0, typename... Tn>
	struct apply : Sx<T0> {};
};

template <typename U0>
*/
struct Sx {
	template <typename...>
	struct apply;

	template <typename T0>
	struct apply<T0> {
		typedef T0 first_;
		typedef val0 type;
	};

	template <typename T0, typename T1>
	struct apply<T0, T1> {
		typedef T0 first_;
		typedef T1 second_;
		typedef val1 type;
	};

	template <typename T0, typename T1, typename T2>
	struct apply<T0, T1, T2> {
		typedef T0 first_;
		typedef T1 second_;
		typedef val2 type;
	};

	template <typename T0, typename T1>
	struct apply<x11::package<key2, key0>, T0, T1> {
		typedef T0 first_;
		typedef T1 second_;
	};

	template <typename T0, typename T1>
	struct apply<x11::package<key3, key1>, T0, T1> {
		typedef T0 first_;
		typedef T1 second_;
	};

	template <typename T0, typename T1, typename T2, typename T3>
	struct apply<T0, T1, T2, T3> {
		typedef T0 first_;
		typedef T1 second_;
		typedef val3 type;
	};

	template <typename T0, typename T1, typename T2, typename T3, typename T4>
	struct apply<T0, T1, T2, T3, T4> {
		typedef T0 first_;
		typedef T1 second_;
		typedef val3 type;
	};
};

template <typename F, typename Map, typename Tpack>
struct unpack_map_impl;

template <typename F, typename Map, typename... Tkey>
struct unpack_map_impl<F, Map, x11::package<Tkey...>> : x11::apply<
	F, x11::package<Tkey...>, typename x11::at<Map, Tkey>::type...
> {};

template <typename F>
struct unpack_map {
	template <typename Map>
	struct apply : unpack_map_impl<
		F, Map, typename x11::transform1<
			Map, x11::first<x11::arg<0>>,
			x11::back_inserter<x11::package<>>
		>::type
        > {};
};

template <typename T>
std::string demangle()
{
        auto *s(abi::__cxa_demangle(typeid(T).name(), 0, 0, 0));
        std::string rv(s);
        free(s);
        return rv;
}

typedef x11::map<x11::pair<key0, val0>, x11::pair<key2, val2>> map11_t;
typedef x11::map<x11::pair<key1, val1>, x11::pair<key3, val3>> map12_t;

int main(int argc, char **argv)
{
	typedef typename x11::apply_wrap<unpack_map<Sx>, map1_t> a1;
	typedef typename x11::apply_wrap<unpack_map<Sx>, map2_t> a2;
	typedef typename x11::apply_wrap<unpack_map<Sx>, map3_t> a3;
	typedef typename x11::apply_wrap<unpack_map<Sx>, map4_t> a4;
	typedef typename x11::apply_wrap<unpack_map<Sx>, map11_t> a5;
	typedef typename x11::apply_wrap<unpack_map<Sx>, map12_t> a6;
	typedef typename x11::apply_wrap<unpack_map<Sx>, x11::erase_key<map4_t, key3>::type> a7;
	
	typedef typename x11::transform1<
		map4_t, x11::first<x11::arg<0>>,
		x11::back_inserter<x11::package<>>
	>::type keys;
	
	std::cout << "w1: " << demangle<keys>() << '\n';
	std::cout << "x1: " << demangle<typename a1::first_>() << '\n';
	std::cout << "x1: " << demangle<typename a1::second_>() << '\n';
	std::cout << "x2: " << demangle<typename a2::first_>() << '\n';
	std::cout << "x2: " << demangle<typename a2::second_>() << '\n';
	std::cout << "x3: " << demangle<typename a3::first_>() << '\n';
	std::cout << "x3: " << demangle<typename a3::second_>() << '\n';
	std::cout << "x4: " << demangle<typename a4::first_>() << '\n';
	std::cout << "x4: " << demangle<typename a4::second_>() << '\n';
	std::cout << "y4: " << demangle<typename a7::first_>() << '\n';
	std::cout << "y4: " << demangle<typename a7::second_>() << '\n';

	std::cout << "x5: " << demangle<typename a5::first_>() << '\n';
	std::cout << "x5: " << demangle<typename a5::second_>() << '\n';
	std::cout << "x6: " << demangle<typename a6::first_>() << '\n';
	std::cout << "x6: " << demangle<typename a6::second_>() << '\n';
	return 0;
}
