/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include "../real_utils.hpp"

#include <boost/spirit/repository/home/qi/numeric/uint.hpp>
#include <boost/spirit/repository/home/qi/numeric/real.hpp>

#include "../measure.hpp"
#include <boost/functional/hash.hpp>

namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace qi_repo = boost::spirit::repository::qi;

std::string numbers;
std::vector<double> result1, result2;

struct strtod_test : test::base {
	void benchmark()
	{
		result1.clear();

		char *start_p;
		char *end_p(const_cast<char *>(numbers.c_str()) - 2);

		while (true) {
			start_p = end_p + 2;
			double d(strtod(start_p, &end_p));
			if (start_p == end_p)
				break;
			result1.push_back(d);
		}

		std::size_t seed(0);
		boost::hash_range(
			seed, result1.begin(), result1.end()
		);
		this->val = seed;
	}
};

struct qi_repo_double_test : test::base {
	static qi::rule<
		std::string::const_iterator,
		std::vector<double>(),
		boost::spirit::standard::space_type
        > p;

	void benchmark()
	{
		result2.clear();
		if (qi::phrase_parse(
			numbers.cbegin(), numbers.cend(), p,
			boost::spirit::standard::space_type(), result2
		)) {
			std::size_t seed(0);
			boost::hash_range(
				seed, result2.begin(), result2.end()
			);
			this->val = seed;
		} else
			this->val = 0;
	}
};

decltype(qi_repo_double_test::p)
qi_repo_double_test::p = qi_repo::double_ % ',';

int main(int argc, char **argv)
{
	int count(5);

	if (argc > 1) {
		if (!qi::parse(
			argv[1], argv[1] + strlen(argv[1]), qi_repo::uint_,
			count
		)) return -1;
	}
	result1.reserve(count);
	result2.reserve(count);

	numbers = make_numbers<double>()(count, std::string(", "));
	std::cout << "Numbers to test: " << numbers << '\n';
	BOOST_SPIRIT_TEST_BENCHMARK(1, (strtod_test)(qi_repo_double_test));

	using karma::lit;
	using karma::double_;

	karma::generate(
		std::ostream_iterator<char>(std::cout),
		lit("result1: ") << (double_ % lit(", ")) << lit('\n'),
		result1
	);

	karma::generate(
		std::ostream_iterator<char>(std::cout),
		lit("result2: ") << (double_ % lit(", ")) << lit('\n'),
		result2
	);

	return test::live_code != 0;
}
