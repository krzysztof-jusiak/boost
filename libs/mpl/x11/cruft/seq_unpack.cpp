#include <cstdio>

#include <boost/mpl/x11/at.hpp>
#include <boost/mpl/x11/map.hpp>
#include <boost/mpl/x11/size.hpp>
#include <boost/mpl/x11/comparison.hpp>
#include <boost/mpl/x11/erase.hpp>
#include <boost/mpl/x11/has_key.hpp>

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace x11 = boost::mpl::x11;

#define N_ARG 20

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

template <typename T, typename Enable = void>
struct x_pack;

#define T_HAS_KEY(z, n, text) x11::has_key<T, key##n>

#define T_X_TYPE(z, n, text) typename x11::at<T, key##n>::type a##n;

#define T_X_TEST(z, n, text) a##n.test();

#define T_PACK(z, n, text) template <typename T>              \
struct x_pack<T, typename std::enable_if<                     \
	x11::and_<                                            \
		x11::equal_to<x11::size<T>, x11::long_<n>>,   \
		BOOST_PP_ENUM_ ## z(n, T_HAS_KEY, nil)        \
	>::value                                              \
>::type> {                                                    \
	static void t()                                       \
	{                                                     \
		BOOST_PP_REPEAT_ ## z(n, T_X_TYPE, nil)       \
		printf("%d: ", n);                            \
		BOOST_PP_REPEAT_ ## z(n, T_X_TEST, nil)       \
	}                                                     \
};

BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(N_ARG), T_PACK, nil)

#define T_RUN(z, n, text) printf("---\n"); x_pack<map##n##_t>::t();

int main(int argc, char **argv)
{
	BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(N_ARG), T_RUN, nil)

	return 0;
}
