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
#include <boost/spirit/repository/home/qi/numeric/numeric_utils.hpp>
#include <boost/spirit/repository/home/qi/auxiliary/static_variant.hpp>

namespace boost { namespace spirit {
namespace repository {
namespace tag {

struct short_ { BOOST_SPIRIT_IS_TAG() };
struct int_ { BOOST_SPIRIT_IS_TAG() };
struct long_ { BOOST_SPIRIT_IS_TAG() };
struct long_long { BOOST_SPIRIT_IS_TAG() };

}

namespace qi {
namespace detail {

template <typename T>
using int_policy = mpl::x11::map<
	mpl::x11::pair<with_extractor, standard::digit_type>,
	mpl::x11::pair<with_integral, small_radix_inserter<T, 10, false>>,
	mpl::x11::pair<
		with_sign, default_sign<char_encoding::standard::char_type>
	>
>;

}

typedef terminal<tag::short_> short_type;
typedef terminal<tag::int_> int_type;
typedef terminal<tag::long_> long_type;
typedef terminal<tag::long_long> long_long_type;

short_type const short_ = short_type();
int_type const int_ = int_type();
long_type const long_ = long_type();
long_long_type const long_long = long_long_type();

}
}

namespace qi {

/*** short_ ***/
template <typename Modifiers>
struct make_primitive<repository::tag::short_, Modifiers>
: repository::qi::make_numeric<
	short, repository::qi::detail::int_policy<short>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::short_, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	short, repository::qi::detail::int_policy<short>
> {};

/*** int_ ***/
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

/*** long_ ***/
template <typename Modifiers>
struct make_primitive<repository::tag::long_, Modifiers>
: repository::qi::make_numeric<
	long, repository::qi::detail::int_policy<long>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::long_, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	long, repository::qi::detail::int_policy<long>
> {};

/*** long_long ***/
template <typename Modifiers>
struct make_primitive<repository::tag::long_long, Modifiers>
: repository::qi::make_numeric<
	long long, repository::qi::detail::int_policy<long long>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::long_long, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	long long, repository::qi::detail::int_policy<long long>
> {};

}

/*** enable short_ ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::short_
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::short_, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::short_, 1
> : mpl::true_ {};

/*** enable int_ ***/
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

/*** enable long_ ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::long_
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::long_, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::long_, 1
> : mpl::true_ {};

/*** enable long_long ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::long_long
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::long_long, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::long_long, 1
> : mpl::true_ {};

}}

#endif
