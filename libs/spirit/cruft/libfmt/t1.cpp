#include <iostream>

double fmtstrtod(char const *s, char **sp);

#define NUM 8

#define NUM_X(s) #s
#define NUM_X1(s) NUM_X(s)
#define NUM_S NUM_X1(NUM)

int main(int argc, char **argv)
{
	char const *in = NUM_S;
	char *sp;
	double out(fmtstrtod(in, &sp));

	std::cout.precision(32);
	std::cout << out << ", " << out - NUM << '\n';
	std::cout << "eq " << (out == NUM) << '\n';
	return 0;
}
