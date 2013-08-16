#include <iostream>
#include <typeinfo>
#include <initializer_list>

#include <boost/spirit/repository/home/support/bignum_utils.hpp>
#include <boost/spirit/repository/home/support/static_table.hpp>
#include <boost/spirit/repository/home/support/detail/rec_pow_2.hpp>

using namespace boost::spirit::repository;

int main(int argc, char **argv)
{
#ifdef __LP64__
	constexpr long radix = 1000000000000000000L;
#else
	constexpr long radix = 1000000000L;
#endif

	std::vector<long> u({123 * (radix / 1000)});
	typedef detail::rec_pow_2<long, int, radix> r_tbl;
	typedef static_table<detail::rec_pow_2<long, int, radix>> tbl;

	printf("%ld, %ld\n", r_tbl::data[1], r_tbl::data[2]);
	for (long x: tbl::get(9))
		printf("xx %ld\n", x);

	auto r(tbl::get(9));
	for (long x: r)
		printf("yy %ld\n", x);

	printf("zz %ld, %ld\n", r[0], r[1]);
	printf("zz1 %ld, %ld\n", *(r.begin() + 0), *(r.begin() + 1));
	std::vector<unsigned long> out(u.size() + r.size());
	bignum_mul<radix>(out, u, r);

	for (auto v : out)
		std::cout << v << ' ';
	std::cout << '\n';
	return 0;
}
