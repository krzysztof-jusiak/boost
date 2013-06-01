/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c)      2011 Bryce Lelbach
    Copyright (c)      2013 Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_UINT_MAY_09_2013_1730)
#define SPIRIT_REPOSITORY_QI_UINT_MAY_09_2013_1730

#include <boost/mpl/x11/map.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_utils.hpp>

namespace boost { namespace spirit {
namespace repository {
namespace tag {

struct ushort_ { BOOST_SPIRIT_IS_TAG() };
struct uint_ { BOOST_SPIRIT_IS_TAG() };
struct ulong_ { BOOST_SPIRIT_IS_TAG() };
struct ulong_long { BOOST_SPIRIT_IS_TAG() };

struct bin { BOOST_SPIRIT_IS_TAG() };
struct oct { BOOST_SPIRIT_IS_TAG() };
struct hex { BOOST_SPIRIT_IS_TAG() };

}

namespace qi {
namespace detail {

template <typename T>
using uint_policy = mpl::x11::map<
	mpl::x11::pair<with_extractor, standard::digit_type>,
	mpl::x11::pair<with_integral, small_radix_integral<T, 10>>
>;

template <typename T>
using bin_policy = mpl::x11::map<
	mpl::x11::pair<
		with_extractor,
		static_char_range<
			mpl::x11::char_<'0'>, mpl::x11::char_<'1'>,
			char_encoding::standard
		>
	>,
	mpl::x11::pair<with_integral, small_radix_integral<T, 2>>
>;

template <typename T>
using oct_policy = mpl::x11::map<
	mpl::x11::pair<
		with_extractor,
		static_char_range<
			mpl::x11::char_<'0'>, mpl::x11::char_<'7'>,
			char_encoding::standard
		>
	>,
	mpl::x11::pair<with_integral, small_radix_integral<T, 8>>
>;

template <typename T>
using hex_policy = mpl::x11::map<
	mpl::x11::pair<with_extractor, standard::xdigit_type>,
	mpl::x11::pair<with_integral, hex_integral<T>>
>;

}

typedef terminal<tag::ushort_> ushort_type;
typedef terminal<tag::uint_> uint_type;
typedef terminal<tag::ulong_> ulong_type;
typedef terminal<tag::ulong_long> ulong_long_type;

typedef terminal<tag::bin> bin_type;
typedef terminal<tag::oct> oct_type;
typedef terminal<tag::hex> hex_type;

ushort_type const ushort_ = ushort_type();
uint_type const uint_ = uint_type();
ulong_type const ulong_ = ulong_type();
ulong_long_type const ulong_long = ulong_long_type();

bin_type const bin = bin_type();
oct_type const oct = oct_type();
hex_type const hex = hex_type();

}
}

namespace qi {

/*** ushort_ ***/
template <typename Modifiers>
struct make_primitive<repository::tag::ushort_, Modifiers>
: repository::qi::make_numeric<
	unsigned short, repository::qi::detail::uint_policy<unsigned short>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<tag::lit, fusion::vector1<A0>>, Modifiers,
	typename enable_if<is_same<
		A0, repository::value_wrapper<unsigned short>
	>>::type
> : repository::qi::make_literal_numeric<
	unsigned short, repository::qi::detail::uint_policy<unsigned short>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::ushort_, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	unsigned short, repository::qi::detail::uint_policy<unsigned short>
> {};

/*** uint_ ***/
template <typename Modifiers>
struct make_primitive<repository::tag::uint_, Modifiers>
: repository::qi::make_numeric<
	unsigned int, repository::qi::detail::uint_policy<unsigned int>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<tag::lit, fusion::vector1<A0>>, Modifiers,
	typename enable_if<is_same<
		A0, repository::value_wrapper<unsigned int>
	>>::type
> : repository::qi::make_literal_numeric<
        unsigned int, repository::qi::detail::uint_policy<unsigned int>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::uint_, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	unsigned int, repository::qi::detail::uint_policy<unsigned int>
> {};

/*** ulong_ ***/
template <typename Modifiers>
struct make_primitive<repository::tag::ulong_, Modifiers>
: repository::qi::make_numeric<
	unsigned long, repository::qi::detail::uint_policy<unsigned long>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<tag::lit, fusion::vector1<A0>>, Modifiers,
	typename enable_if<is_same<
		A0, repository::value_wrapper<unsigned long>
	>>::type
> : repository::qi::make_literal_numeric<
        unsigned long, repository::qi::detail::uint_policy<unsigned long>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::ulong_, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	unsigned long, repository::qi::detail::uint_policy<unsigned long>
> {};

/*** ulong_long ***/
template <typename Modifiers>
struct make_primitive<repository::tag::ulong_long, Modifiers>
: repository::qi::make_numeric<
	unsigned long long,
	repository::qi::detail::uint_policy<unsigned long long>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<tag::lit, fusion::vector1<A0>>, Modifiers,
	typename enable_if<is_same<
		A0, repository::value_wrapper<unsigned long long>
	>>::type
> : repository::qi::make_literal_numeric<
        unsigned long long,
	repository::qi::detail::uint_policy<unsigned long long>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::ulong_long, fusion::vector1<A0>>,
	Modifiers
> : repository::qi::make_direct_numeric<
	unsigned long long,
	repository::qi::detail::uint_policy<unsigned long long>
> {};

/*** bin ***/
template <typename Modifiers>
struct make_primitive<repository::tag::bin, Modifiers>
: repository::qi::make_numeric<
	unsigned int, repository::qi::detail::bin_policy<unsigned int>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::bin, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	unsigned int,
	repository::qi::detail::bin_policy<unsigned int>
> {};

/*** oct ***/
template <typename Modifiers>
struct make_primitive<repository::tag::oct, Modifiers>
: repository::qi::make_numeric<
	unsigned int, repository::qi::detail::oct_policy<unsigned int>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::oct, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	unsigned int,
	repository::qi::detail::oct_policy<unsigned int>
> {};

/*** hex ***/
template <typename Modifiers>
struct make_primitive<repository::tag::hex, Modifiers>
: repository::qi::make_numeric<
	unsigned int, repository::qi::detail::hex_policy<unsigned int>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::hex, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	unsigned int,
	repository::qi::detail::hex_policy<unsigned int>
> {};

}

/*** enable ushort_ ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::ushort_
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<tag::lit, fusion::vector1<A0>>,
	typename enable_if<is_same<
		A0, repository::value_wrapper<unsigned short>
	>>::type
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::ushort_, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::ushort_, 1
> : mpl::true_ {};

/*** enable uint_ ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::uint_
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<tag::lit, fusion::vector1<A0>>,
	typename enable_if<is_same<
		A0, repository::value_wrapper<unsigned int>
	>>::type
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::uint_, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::uint_, 1
> : mpl::true_ {};

/*** enable ulong_ ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::ulong_
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<tag::lit, fusion::vector1<A0>>,
	typename enable_if<is_same<
		A0, repository::value_wrapper<unsigned long>
	>>::type
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::ulong_, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::ulong_, 1
> : mpl::true_ {};

/*** enable ulong_long ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::ulong_long
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<tag::lit, fusion::vector1<A0>>,
	typename enable_if<is_same<
		A0, repository::value_wrapper<unsigned long long>
	>>::type
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<
		repository::tag::ulong_long, fusion::vector1<A0>
	>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::ulong_long, 1
> : mpl::true_ {};

/*** enable bin ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::bin
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::bin, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::bin, 1
> : mpl::true_ {};

/*** enable oct ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::oct
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::oct, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::oct, 1
> : mpl::true_ {};

/*** enable hex ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::hex
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::hex, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::hex, 1
> : mpl::true_ {};

}}

#endif
