/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_SPIRIT_OPTIMIZATION_REAL_UTILS_JUL_18_2013_1250)
#define BOOST_SPIRIT_OPTIMIZATION_REAL_UTILS_JUL_18_2013_1250

#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <boost/random/random_device.hpp>
#include <boost/random/uniform_smallint.hpp>
#include <boost/random/normal_distribution.hpp>

#include <boost/iterator/function_input_iterator.hpp>

template <int MaxDigits, int MaxExponent, bool Signed>
struct real_generator {
	static boost::random_device src;
	typedef std::string result_type;

	result_type operator()()
	{
		using namespace boost::random;
		namespace karma = boost::spirit::karma;
		using karma::int_;
		using karma::lit;

		std::string rv;

		auto m_size_r(normal_distribution<>(
			0, double(MaxDigits) / 2
		)(src));
		auto m_size(std::lround(std::fabs(m_size_r)));

		if (Signed && std::signbit(m_size_r))
			rv.push_back('-');

		if (!m_size) {
			rv.push_back('0');
			return rv;
		} else if (m_size > MaxDigits)
			m_size = MaxDigits;

		auto dot_pos(uniform_smallint<>(0, m_size)(src));
		boost::random::uniform_smallint<> digit_dist(0, 9);
		decltype(dot_pos) pos(0);

		for (; pos < dot_pos; ++pos)
			rv.push_back(digit_dist(src) + 0x30);

		if (pos < m_size) {
			rv.push_back('.');
			for (; pos < m_size; ++pos)
				rv.push_back(digit_dist(src) + 0x30);
		}

		if (MaxExponent) {
			auto exp_r(normal_distribution<>(
				0, double(MaxExponent) / 4
			)(src));
			auto exp(std::lround(exp_r));
			if (exp) {
				karma::generate(
					std::back_inserter(rv),
					lit('e') << int_, exp
				);
			}
		}
		return rv;
	}
};

template <int MaxDigits, int MaxExponent, bool Signed>
boost::random_device real_generator<MaxDigits, MaxExponent, Signed>::src;

template <typename T>
struct make_numbers {
	template <typename CharT>
	std::string operator()(
		size_t count, std::basic_string<CharT> const &delim
	)
	{
		namespace karma = boost::spirit::karma;
		using karma::string;
		using karma::lit;

		real_generator<18, 308, true> r;
		std::string rv;

		karma::generate(
			std::back_inserter(rv),
			string % lit(delim),
			boost::make_iterator_range(
				boost::make_function_input_iterator(
					r, size_t(0)
				),
				boost::make_function_input_iterator(r, count)
			)
		);
		return rv;
	}
};

#endif
