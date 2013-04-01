/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300

#if defined(_MSC_VER)
#pragma once
#endif

#include <type_traits>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

/* mpl::and<> is using old-school preprocessor magic to emulate variadic
 * semantics. On the other hand, GNU c++11 implementation provides a true
 * variadic std::__and_<>, which is rather more usable.
 */

template <typename T, typename Policy, typename Enable = void>
struct numeric_impl {
	template <typename Iterator, typename Attribute>
	static bool
	parse(Iterator& first, Iterator const& last, Attribute& attr,
	      Policy const& p);
};

template <typename T, typename Policy>
struct numeric_impl<
	T, Policy, typename std::enable_if<
		std::and_<
			
			mpl::has_key<Policy, with_extractor>,
			mpl::has_key<Policy, with_mapper>,
			mpl::has_key<Policy, with_inserter>,
			mpl::equal_to<mpl::size<T>, mpl::int_<3> >
		>
	>::type
> {
	template <typename Iterator, typename Attribute>
	static bool
	parse(Iterator& first, Iterator const& last, Attribute& attr,
	      Policy const& p);
};

template <typename T, typename Policy>
struct numeric_impl<
	T, Policy, typename boost::enable_if<
		mpl::and_<
			mpl::has_key<Policy, with_extractor>,
			mpl::has_key<Policy, with_mapper>,
			mpl::has_key<Policy, with_inserter>,
			mpl::has_key<Policy, with_sign>,
			mpl::equal_to<mpl::size<T>, mpl::int_<4> >
		>
	>::type
> {
	template <typename Iterator, typename Attribute>
	static bool
	parse(Iterator& first, Iterator const& last, Attribute& attr,
	      Policy const& p);
};


}
}}}}

#endif
