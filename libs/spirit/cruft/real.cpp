#include <cstdio>
#include <vector>

#include <boost/spirit/home/qi/nonterminal.hpp>
//#include <boost/spirit/home/qi/numeric.hpp>
//#include "boost/spirit/repository/home/qi/numeric/real.hpp"
#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/string.hpp>

//namespace qi = boost::spirit::qi;
//namespace qi_repo = boost::spirit::repository::qi;

namespace mpl = boost::mpl;

#define N_ARG 10

#define T_KEY(z, n, text) struct key##n {};

BOOST_PP_REPEAT(N_ARG, T_KEY, nil)

#define T_VAL(z, n, text) struct val##n { \
void test() { printf("val %d\n", n); }    \
};

BOOST_PP_REPEAT(N_ARG, T_VAL, nil)

#define T_MAP_PAIR(z, n, text) mpl::pair<key##n, val##n>

#define T_MAP(z, n, text) typedef mpl::map< \
BOOST_PP_ENUM_ ## z(n, T_MAP_PAIR, nil)     \
> map##n##_t;

BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(N_ARG), T_MAP, nil)

template <typename T, typename Enable = void>
struct x_pack;

#define T_HAS_KEY(z, n, text) mpl::has_key<T, key##n>

#define T_X_TYPE(z, n, text) typename mpl::at<T, key##n>::type a##n;

#define T_X_TEXT(z, n, text) a##n.test();

#define T_PACK(z, n, text) <typename T>                     \
struct x_pack<T, typename boost::enable_if<                 \
	mpl::and_<                                          \
		mpl::equal_to<mpl::size<T>, mpl::int_<##n>, \
		BOOST_PP_ENUM_ ## z(n, T_HAS_KEY, nil)      \
	>                                                   \
>::type> {                                                  \
	static void t()                                     \
	{                                                   \
		BOOST_PP_REPEAT_ ## z(n, T_X_TYPE, nil)     \
		printf("%d: ", n);                          \
		BOOST_PP_REPEAT_ ## z(n, T_X_TEST, nil)     \
	}                                                   \
};

//BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(N_ARG), T_MAP, nil)


template <typename T>
struct x_pack<T, typename boost::enable_if<
	mpl::and_<
		mpl::has_key<T, key0>,
		mpl::equal_to<mpl::size<T>, mpl::int_<1> >
	>
>::type > {
	static void t()
	{
		typename mpl::at<T, key0>::type a;
		printf("1: ");
		a.test();
	}
};

template <typename T>
struct x_pack<T, typename boost::enable_if<
	mpl::and_<
		mpl::has_key<T, key0>,
		mpl::has_key<T, key1>,
		mpl::equal_to<mpl::size<T>, mpl::int_<2> >
	>
>::type > {
	static void t()
	{
		typename mpl::at<T, key0>::type a;
		typename mpl::at<T, key1>::type b;
		printf("2: ");
		a.test();
		b.test();
		x_pack<typename mpl::erase_key<T, key1>::type >::t();
	}
};

int main(int argc, char **argv)
{
	std::string t_str("1.1, 1.2, 1.3, 1.4");
	std::vector<double> res;

	x_pack<map1_t>::t();
	printf("---\n");
	x_pack<map2_t>::t();

/*
	qi::rule<std::string::iterator, std::vector<double>()> p(
		qi_repo::double_ % ", "
	);

	bool rv(qi::parse(t_str.begin(), t_str.end(), p, res));

	size_t cnt;
	printf("rv %d, ", rv);
	for (cnt = 0; (cnt + 1) < res.size(); ++cnt)
		printf("%f, ", res[cnt]);

	if (!res.empty())
		printf("%f\n", res[cnt]);
	*/
	return 0;
}
