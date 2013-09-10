/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_REAL_MAR_13_2013_2300)
#define SPIRIT_REPOSITORY_QI_REAL_MAR_13_2013_2300

#include <boost/mpl/x11/map.hpp>
#include <boost/mpl/x11/insert.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric.hpp>
#include <boost/spirit/repository/home/qi/numeric/detail/decimal_real_wrapper.hpp>

namespace boost { namespace spirit {
namespace repository {
namespace tag {

struct float_ { BOOST_SPIRIT_IS_TAG() };
struct double_ { BOOST_SPIRIT_IS_TAG() };
struct long_double { BOOST_SPIRIT_IS_TAG() };

}

namespace qi {

template <typename T>
using precise_ureal_policy = mpl::x11::map<
	mpl::x11::pair<with_extractor, standard::digit_type>,
	mpl::x11::pair<with_integer,
		typename detail::decimal_real_wrapper<T>
			       ::template integer_op<false>
	>,
	mpl::x11::pair<with_fraction, mpl::x11::pair<
		detail::default_fractional_separator<
			char_encoding::standard::char_type
		>,
		typename detail::decimal_real_wrapper<T>
			       ::template fraction_op<false>
	>>,
	mpl::x11::pair<with_exponent, mpl::x11::pair<
		detail::default_exponent_separator<
			char_encoding::standard::char_type
		>,
		typename detail::decimal_real_wrapper<T>
			       ::template exponent_op<false>
	>>,
	mpl::x11::pair<with_exponent_sign,
		detail::default_sign<char_encoding::standard::char_type>
	>,
	mpl::x11::pair<with_wrapper, detail::decimal_real_wrapper<T>>,
	mpl::x11::pair<with_special, detail::default_fp_special_values<
		T, char_encoding::standard::char_type
	>>
>;

template <typename T>
using precise_real_policy = typename mpl::x11::insert<
	precise_ureal_policy<T>,
	mpl::x11::pair<with_sign,
		detail::default_sign<char_encoding::standard::char_type>
	>
>::type;

template <typename T>
using fast_ureal_policy = mpl::x11::map<
	mpl::x11::pair<with_extractor, standard::digit_type>,
	mpl::x11::pair<with_integer,
		detail::unchecked_ascii_integer<T, 10>
	>,
	mpl::x11::pair<with_fraction, mpl::x11::pair<
		detail::default_fractional_separator<
			char_encoding::standard::char_type
		>,
		detail::unchecked_ascii_fraction<T, 10>
	>>,
	mpl::x11::pair<with_exponent, mpl::x11::pair<
		detail::default_exponent_separator<
			char_encoding::standard::char_type
		>,
		detail::unchecked_ascii_exponent<T, 10>
	>>,
	mpl::x11::pair<with_exponent_sign,
		detail::default_sign<char_encoding::standard::char_type>
	>
>;

template <typename T>
using fast_real_policy = typename mpl::x11::insert<
	fast_ureal_policy<T>,
	mpl::x11::pair<with_sign,
		detail::default_sign<char_encoding::standard::char_type>
	>
>::type;

typedef terminal<tag::float_> float_type;
typedef terminal<tag::double_> double_type;
typedef terminal<tag::long_double> long_double_type;

float_type const float_ = float_type();
double_type const double_ = double_type();
long_double_type const long_double = long_double_type();

}
}

namespace qi {

/*** float_ ***/
template <typename Modifiers>
struct make_primitive<repository::tag::float_, Modifiers>
: repository::qi::make_numeric<
	float, repository::qi::precise_real_policy<float>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<tag::lit, fusion::vector1<A0>>, Modifiers,
	typename enable_if<is_same<
		A0, repository::value_wrapper<float>
	>>::type
> : repository::qi::make_literal_numeric<
	float, repository::qi::precise_real_policy<float>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::float_, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	float, repository::qi::precise_real_policy<float>
> {};

/*** double_ ***/
template <typename Modifiers>
struct make_primitive<repository::tag::double_, Modifiers>
: repository::qi::make_numeric<
	double, repository::qi::precise_real_policy<double>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<tag::lit, fusion::vector1<A0>>, Modifiers,
	typename enable_if<is_same<
		A0, repository::value_wrapper<double>
	>>::type
> : repository::qi::make_literal_numeric<
	double, repository::qi::precise_real_policy<double>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::double_, fusion::vector1<A0>>, Modifiers
> : repository::qi::make_direct_numeric<
	double, repository::qi::precise_real_policy<double>
> {};

/*** long_double ***/
template <typename Modifiers>
struct make_primitive<repository::tag::long_double, Modifiers>
: repository::qi::make_numeric<
	long double, repository::qi::precise_real_policy<long double>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<tag::lit, fusion::vector1<A0>>, Modifiers,
	typename enable_if<is_same<
		A0, repository::value_wrapper<long double>
	>>::type
> : repository::qi::make_literal_numeric<
	long double, repository::qi::precise_real_policy<long double>
> {};

template <typename Modifiers, typename A0>
struct make_primitive<
	terminal_ex<repository::tag::long_double, fusion::vector1<A0>>,
	Modifiers
> : repository::qi::make_direct_numeric<
	long double, repository::qi::precise_real_policy<long double>
> {};

}

/*** enable float_ ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::float_
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<tag::lit, fusion::vector1<A0>>,
	typename enable_if<is_same<
		A0, repository::value_wrapper<float>
	>>::type
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::float_, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::float_, 1
> : mpl::true_ {};

/*** enable double_ ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::double_
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<tag::lit, fusion::vector1<A0>>,
	typename enable_if<is_same<
		A0, repository::value_wrapper<double>
	>>::type
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<repository::tag::double_, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::double_, 1
> : mpl::true_ {};

/*** enable long_double ***/
template <>
struct use_terminal<
	qi::domain, repository::tag::long_double
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain, terminal_ex<tag::lit, fusion::vector1<A0>>,
	typename enable_if<is_same<
		A0, repository::value_wrapper<long double>
	>>::type
> : mpl::true_ {};

template <typename A0>
struct use_terminal<
	qi::domain,
	terminal_ex<repository::tag::long_double, fusion::vector1<A0>>
> : is_arithmetic<A0> {};

template <>
struct use_lazy_terminal<
	qi::domain, repository::tag::long_double, 1
> : mpl::true_ {};

}}

#endif
