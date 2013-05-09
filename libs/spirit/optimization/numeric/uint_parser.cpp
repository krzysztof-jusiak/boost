/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/


#include <string>
#include <vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/random/random_device.hpp>
#include <boost/iterator/function_input_iterator.hpp>
#include <boost/spirit/repository/home/qi/numeric/uint.hpp>

#include "../measure.hpp"

namespace x11 = boost::mpl::x11;
namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace qi_repo = boost::spirit::repository::qi;

template <typename T>
void make_numbers(
	std::vector<T> &out, size_t count,
	std::basic_string<T> const &delim
)
{
	using karma::uint_;
	using karma::lit;

	boost::random_device r;

	karma::generate(
		std::back_inserter(out),
		uint_ % lit(delim),
		boost::make_iterator_range(
			boost::make_function_input_iterator(r, size_t(0)),
			boost::make_function_input_iterator(r, count)
		)
	);
}

int main(int argc, char **argv)
{
	int count(5);

	if (argc > 1) {
		if (!qi::parse(
			argv[1], argv[1] + strlen(argv[1]), qi_repo::uint_,
			count
		)) return -1;
	}

	std::vector<char> numbers;
	make_numbers(numbers, count, std::string(", "));
	numbers.push_back(0);
	std::cout << "Numbers to test: " << &numbers.front() << '\n';
	return 0;
}
