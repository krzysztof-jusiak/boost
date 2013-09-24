/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#define BOOST_TEST_MODULE spirit
#include <boost/test/included/unit_test.hpp>

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/home/qi/numeric/real.hpp>

#include "../optimization/real_utils.hpp"

#define CASE_COUNT 10000

namespace boost { namespace spirit { namespace repository { namespace qi {

BOOST_AUTO_TEST_CASE(real3_0)
{
	std::string numbers(make_numbers<double>()(
		CASE_COUNT, std::string(", ")
	));

	BOOST_TEST_MESSAGE("Test values: " << numbers);

	std::vector<double> result_ref;
	char *start_p;
	char *end_p(const_cast<char *>(numbers.c_str()) - 2);
	while (true) {
		start_p = end_p + 2;
		double d(strtod(start_p, &end_p));
		if (start_p == end_p)
			break;
		result_ref.push_back(d);
	}

	std::vector<double> result_test;

	spirit::qi::rule<
		std::string::const_iterator,
		std::vector<double>(),
		boost::spirit::standard::space_type
	> p = double_ % ',';

	BOOST_CHECK(spirit::qi::phrase_parse(                      \
		numbers.cbegin(), numbers.cend(), p,               \
		boost::spirit::standard::space_type(), result_test \
	));

	BOOST_CHECK_EQUAL_COLLECTIONS(                   \
		result_ref.cbegin(), result_ref.cend(),  \
		result_test.cbegin(), result_test.cend() \
	);
}

}}}}
