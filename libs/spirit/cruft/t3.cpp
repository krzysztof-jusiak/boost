#include <iostream>
#include <typeinfo>
#include <initializer_list>

#include <boost/spirit/repository/home/support/bignum_utils.hpp>
#include <boost/spirit/repository/home/support/static_table.hpp>
#include <boost/spirit/repository/home/support/detail/rec_pow_2.hpp>

using namespace boost::spirit::repository;

int main(int argc, char **argv)
{
	//constexpr long radix = 1000000000000000000L;
	constexpr long radix = 1000000000L;

	std::vector<unsigned long> u({123 * (radix / 1000)});
	typedef static_table<detail::rec_pow_2<long, int, radix>> tbl;
	auto r(tbl::get(4));
	std::vector<unsigned long> out(u.size() + r.size());
	bignum_mul<radix>(out, u, r);

	for (auto v : out)
		std::cout << v << ' ';
	std::cout << '\n';
	return 0;
}
