/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c)      2011 Bryce Lelbach
    Copyright (c)      2013 Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_UINT_MAY_09_2013_1730)
#define SPIRIT_REPOSITORY_QI_UINT_MAY_09_2013_1730

#include <boost/spirit/repository/home/qi/numeric/numeric.hpp>
#include <boost/mpl/x11/map.hpp>

namespace boost { namespace spirit {
namespace repository {
namespace tag {

struct uint_ {
	BOOST_SPIRIT_IS_TAG()
};

}

namespace qi {
namespace detail {

template <typename T>
using uint_policy = mpl::x11::map<
	mpl::x11::pair<with_extractor, standard::digit_type>,
	mpl::x11::pair<with_inserter, default_inserter<T>>
>;

}

typedef terminal<tag::uint_> uint_type;
uint_type const uint_ = uint_type();

}
}

namespace qi {

template <typename Modifiers>
struct make_primitive<repository::tag::uint_, Modifiers>
: repository::qi::make_numeric<
	unsigned int, repository::qi::detail::uint_policy<unsigned int>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::uint_, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	unsigned int, repository::qi::detail::uint_policy<unsigned int>
> {};

}

template <>
struct use_terminal<
	qi::domain, repository::tag::uint_
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::uint_, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::uint_, 1
> : mpl::true_ {};

}}

#endif
