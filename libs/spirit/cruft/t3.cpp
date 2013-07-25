#include <iostream>
#include <typeinfo>

#include <boost/spirit/repository/home/support/static_table.hpp>
#include <boost/spirit/repository/home/support/detail/rec_pow_2.hpp>

using namespace boost::spirit::repository;

int main(int argc, char **argv)
{
	//constexpr long radix = 1000000000000000000L;
	constexpr long radix = 1000000000L;
	typedef static_table<detail::rec_pow_2<long, int, radix>> tbl;

	auto r(tbl::get(15));

	for (auto v : r)
		std::cout << v << ' ';
	std::cout << '\n';
	return 0;
}
