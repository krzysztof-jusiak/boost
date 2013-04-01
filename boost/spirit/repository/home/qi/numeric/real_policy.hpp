/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_REAL_POLICY_MAR_30_2013_2300)
#define SPIRIT_REPOSITORY_QI_REAL_POLICY_MAR_30_2013_2300

#include <boost/spirit/repository/home/qi/numeric/traits.hpp>

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost { namespace spirit { namespace repository { namespace qi {

struct digit_extractor {
	template <typename Iterator>
	bool operator()(Iterator &first, Iterator const &last,
			typename std::iterator_traits<Iterator>::value_type &c)
	{
		return true;
	}
};

template <int Radix>
struct small_radix_mapper {
	template <typename Char>
	bool operator()(Char c, int &digit)
	{
		static const int lsd(Char('0'));
		static const int msd(Char('0') + Radix);

		digit = int(c) - lsd;
		return digit < msd;
	}
};

template <typename T, int Radix>
struct radix_inserter {
	bool operator()(int digit, T &val)
	{
		val = val * Radix + digit;
		return true;
	}
};

namespace detail
{

template <typename T>
struct real_policy {
	typedef mpl::map<
		mpl::pair<with_extractor, digit_extractor>,
		mpl::pair<with_mapper, small_radix_mapper<10> >,
		mpl::pair<with_inserter, radix_inserter<T, 10> >
	> type;
};

}
}}}}

#endif
