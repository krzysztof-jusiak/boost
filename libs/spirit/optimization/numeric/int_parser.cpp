/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/


#include <string>
#include <vector>
#include <ext/numeric>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/random/random_device.hpp>
#include <boost/iterator/function_input_iterator.hpp>
#include <boost/spirit/repository/home/qi/numeric/int.hpp>

#include "../measure.hpp"

namespace x11 = boost::mpl::x11;
namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace qi_repo = boost::spirit::repository::qi;

struct random_device {
	static boost::random_device src;
	typedef int result_type;

	int operator()()
	{
		unsigned int v1(src()), v2(src());
		int sign(0x80000000 & v2 ? -1 : 1);
		return sign * (v1 % __gnu_cxx::power(10, v2 % 10));
	}
};

boost::random_device random_device::src;

template <typename T>
void make_numbers(
	std::vector<T> &out, size_t count,
	std::basic_string<T> const &delim
)
{
	using karma::int_;
	using karma::lit;

	random_device r;

	karma::generate(
		std::back_inserter(out),
		int_ % lit(delim),
		boost::make_iterator_range(
			boost::make_function_input_iterator(r, size_t(0)),
			boost::make_function_input_iterator(r, count)
		)
	);
}

std::vector<char> numbers;
std::vector<int> result1, result2;

struct qi_int_test : test::base {
	static qi::rule<
		std::vector<char>::const_iterator,
		std::vector<int>(),
		boost::spirit::standard::space_type
        > p;

	void benchmark()
	{
		result1.clear();
		if (qi::phrase_parse(
			numbers.cbegin(), numbers.cend(), p,
			boost::spirit::standard::space_type(), result1
		))
			this->val = std::accumulate(
				result1.begin(), result1.end(), 0
			);
		else
			this->val = 0;
	}
};

decltype(qi_int_test::p) qi_int_test::p = qi::int_ % ',';

struct qi_repo_int_test : test::base {
	static qi::rule<
		std::vector<char>::const_iterator,
		std::vector<int>(),
		boost::spirit::standard::space_type
        > p;

	void benchmark()
	{
		result2.clear();
		if (qi::phrase_parse(
			numbers.cbegin(), numbers.cend(), p,
			boost::spirit::standard::space_type(), result2
		))
			this->val = std::accumulate(
				result2.begin(), result2.end(), 0
			);
		else
			this->val = 0;
	}
};

decltype(qi_repo_int_test::p) qi_repo_int_test::p = qi_repo::int_ % ',';

int main(int argc, char **argv)
{
	int count(5);

	if (argc > 1) {
		if (!qi::parse(
			argv[1], argv[1] + strlen(argv[1]), qi_repo::int_,
			count
		)) return -1;
	}
	result1.reserve(count);
	result2.reserve(count);

	make_numbers(numbers, count, std::string(", "));
	numbers.push_back(0);
	std::cout << "Numbers to test: " << &numbers.front() << '\n';

	BOOST_SPIRIT_TEST_BENCHMARK(1000, (qi_int_test)(qi_repo_int_test));

	using karma::lit;
	using karma::int_;

	karma::generate(
		std::ostream_iterator<char>(std::cout),
		lit("result1: ") << (int_ % lit(", ")) << lit('\n'),
		result1
	);

	karma::generate(
		std::ostream_iterator<char>(std::cout),
		lit("result2: ") << (int_ % lit(", ")) << lit('\n'),
		result2
	);

	return test::live_code != 0;
}
