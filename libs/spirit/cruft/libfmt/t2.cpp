#include <iostream>
#include <boost/spirit/repository/home/qi/numeric/detail/decimal_real_wrapper.hpp>

int main(int argc, char **argv)
{
	boost::spirit::repository::qi::detail::decimal_real_wrapper<float> x;
	x.mantissa.assign({1, 2, 3});
	x.int_scale = 1;

	float out(static_cast<float>(x));
	std::cout.precision(32);
	std::cout << "x: " << out << ", " << out - 1.23f << '\n';
	std::cout << "y: " << 1.23f << '\n';
	std::cout << "eq " << (out == 1.23f) << '\n';

	boost::spirit::repository::qi::detail::decimal_real_wrapper<double> x1;
	x1.mantissa.assign({1, 2, 3});
	x1.int_scale = 1;

	double out1(static_cast<double>(x1));
	std::cout.precision(32);
	std::cout << "x: " << out1 << ", " << out1 - 1.23 << '\n';
	std::cout << "y: " << 1.23 << '\n';
	std::cout << "eq " << (out1 == 1.23) << '\n';

	boost::spirit::repository::qi::detail::decimal_real_wrapper<long double> x2;
	x2.mantissa.assign({1, 2, 3});
	x2.int_scale = 1;

	long double out2(static_cast<long double>(x2));
	std::cout.precision(32);
	std::cout << "x: " << out2 << ", " << out2 - 1.23l << '\n';
	std::cout << "y: " << 1.23l << '\n';
	std::cout << "eq " << (out2 == 1.23l) << '\n';

/*
	in = "1.23456789012345678901234567890123456789";
	out = fmtstrtod(in, &sp);
	std::cout << out << ", " << out - 1.23456789012345678901234567890123456789 << '\n';
	std::cout << "eq " << (out == 1.23456789012345678901234567890123456789) << '\n';

	in = "9.025971879324147880346310405869e-277";
	out = fmtstrtod(in, &sp);
	std::cout << out << ", " << out - 9.025971879324147880346310405869e-277 << '\n';
	std::cout << "eq " << (out == 9.025971879324147880346310405869e-277) << '\n';
*/
}
