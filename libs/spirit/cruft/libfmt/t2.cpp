#include <iostream>
#include <boost/spirit/repository/home/qi/numeric/detail/decimal_real_wrapper.hpp>

int main(int argc, char **argv)
{
	boost::spirit::repository::qi::detail::decimal_real_wrapper<double> x;
	x.mantissa.assign({1, 2, 3});
	x.scale = 1;

	double out(static_cast<double>(x));
	std::cout.precision(32);
	std::cout << out << ", " << out - 1.23 << '\n';
	std::cout << "eq " << (out == 1.23) << '\n';
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
