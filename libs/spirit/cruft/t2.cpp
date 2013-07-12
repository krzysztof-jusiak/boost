#include <iostream>
#include <typeinfo>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/home/qi/numeric/real.hpp>

using namespace boost::spirit::repository::qi;

template <typename T>
struct ref_cvt {
	std::string const &s;

	ref_cvt(std::string const &s_)
	: s(s_) {}

	operator T() const;
};

template <>
ref_cvt<float>::operator float() const
{
	return strtof(s.c_str(), nullptr);
}

template <>
ref_cvt<double>::operator double() const
{
	return strtod(s.c_str(), nullptr);
}

template <>
ref_cvt<long double>::operator long double() const
{
	return strtold(s.c_str(), nullptr);
}

template <typename T>
void test_arg(T arg, char const *arg_ref)
{
	numeric_parser<T, precise_real_policy<T>> p;
	std::string in(arg_ref);
	T val_t, val_r = ref_cvt<T>(in);

	boost::spirit::qi::parse(in.cbegin(), in.cend(), p, val_t);
	std::cout.precision(32);
	std::cout << "with type " << typeid(T).name() << '\n';
	std::cout << "  x: " << val_t << '\n';
	std::cout << "  y: " << val_r << '\n';
	std::cout << "  eq: " << (val_t == val_r)
		  << " delta: " << (val_t - val_r) << '\n';
}

#define TESTARG(t, x) test_arg<t>(x, #x)

int main(int argc, char **argv)
{
#ifdef WORKING
	TESTARG(float, 1.23);
	TESTARG(double, 1.23);
	TESTARG(long double, 1.23);

	TESTARG(double, 1.23e+20);
	TESTARG(long double, 1.23e+20);
#endif

#ifdef NOT_WORKING
	TESTARG(float, 1.23e+20);
#endif

	TESTARG(double, 1.23e-20);

	return 0;
}