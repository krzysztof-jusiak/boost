/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300

#include <boost/spirit/repository/home/qi/numeric/numeric_policy.hpp>
#include <boost/mpl/x11/package.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

struct numeric_impl {
	template <typename...>
	struct apply;

	template <typename Extractor, typename Inserter>
	struct apply<
		boost::mpl::x11::package<with_extractor, with_inserter>,
		Extractor, Inserter
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <typename Extractor, typename Inserter, typename Mapper>
	struct apply<
		boost::mpl::x11::package<
			with_extractor, with_inserter, with_mapper
		>, Extractor, Inserter, Mapper
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};
};

template <typename Extractor, typename Inserter, typename Mapper>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_inserter, with_mapper
	>, Extractor, Inserter, Mapper
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	return true;
}

}
}}}}

#endif
