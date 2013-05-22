/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c)      2011 Bryce Lelbach
    Copyright (c)      2013 Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_INT_MAY_21_2013_2300)
#define SPIRIT_REPOSITORY_QI_INT_MAY_21_2013_2300

#include <boost/mpl/x11/map.hpp>
#include <boost/mpl/x11/list.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric.hpp>
#include <boost/spirit/repository/home/qi/char/static_char.hpp>
#include <boost/spirit/repository/home/qi/auxiliary/static_variant.hpp>

namespace boost { namespace spirit {
namespace repository {
namespace tag {

struct int_ {
	BOOST_SPIRIT_IS_TAG()
};

}

namespace qi {
namespace detail {

template <typename T>
using int_policy = mpl::x11::map<
	mpl::x11::pair<with_extractor, standard::digit_type>,
	mpl::x11::pair<with_inserter, default_inserter<T>>,
	mpl::x11::pair<with_sign, static_variant<
		mpl::x11::pair<
			static_char<mpl::x11::char_<'-'>>,
			mpl::x11::true_type
		>,
		mpl::x11::pair<
			static_char<mpl::x11::char_<'+'>>,
			mpl::x11::false_type
		>
	>>
>;

}

typedef terminal<tag::int_> int_type;
int_type const int_ = int_type();

}
}

namespace qi {

template <typename Modifiers>
struct make_primitive<repository::tag::int_, Modifiers>
: repository::qi::make_numeric<
	int, repository::qi::detail::int_policy<int>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::int_, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	int, repository::qi::detail::int_policy<int>
> {};

}

template <>
struct use_terminal<
	qi::domain, repository::tag::int_
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::int_, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::int_, 1
> : mpl::true_ {};

}}

#endif
