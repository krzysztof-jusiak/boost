#include <iostream>
#include <typeinfo>
#include <initializer_list>

#include <boost/spirit/repository/home/support/bignum_utils.hpp>
#include <boost/spirit/repository/home/support/static_table.hpp>
#include <boost/spirit/repository/home/support/detail/rec_pow_2.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/home/qi/numeric/real.hpp>

using namespace boost::spirit::repository;

int main(int argc, char **argv)
{
#ifdef __LP64__
	constexpr long radix = 100000000000000000L;
#else
	constexpr long radix = 100000000L;
#endif
	char const *xs = "4294967296";
	unsigned int xi = strtoul(xs, 0, 10);
	printf("-- %u\n", xi);
	std::vector<long> u({100 * (radix / 1000)});
	//std::vector<long> u({
	//	0L, 0L, 1562500L, 83404541L, 70211815L, 23125782L, 55511151L
	//});
	typedef static_table<detail::rec_pow_2<long, int, radix>> r_tbl;

	auto r(r_tbl::get(7));
	printf("r: ");
	for (auto v: r)
		std::cout << v << ' ';
	std::cout << '\n';

	std::vector<long> out(u.size() + r.size());
	bignum_mul<radix>(out, u, r);

	printf("out: ");
	for (auto v: out)
		std::cout << v << ' ';
	std::cout << '\n';
	return 0;
}
