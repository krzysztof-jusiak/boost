#include <iostream>

double fmtstrtod(char const *s, char **sp);

int main(int argc, char **argv)
{
	char const *in = "1e23";
	char *sp;
	double out(fmtstrtod(in, &sp));

	std::cout.precision(32);
	std::cout << out << ", " << out - 1e23 << '\n';
	std::cout << "eq " << (out == 1e23) << '\n';

	in = "1.23456789012345678901234567890123456789";
	out = fmtstrtod(in, &sp);
	std::cout << out << ", " << out - 1.23456789012345678901234567890123456789 << '\n';
	std::cout << "eq " << (out == 1.23456789012345678901234567890123456789) << '\n';

	in = "9.025971879324147880346310405869e-277";
	out = fmtstrtod(in, &sp);
	std::cout << out << ", " << out - 9.025971879324147880346310405869e-277 << '\n';
	std::cout << "eq " << (out == 9.025971879324147880346310405869e-277) << '\n';
}
