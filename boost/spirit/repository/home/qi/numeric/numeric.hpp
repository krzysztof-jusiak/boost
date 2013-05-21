/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011      Bryce Lelbach
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_MAR_13_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_MAR_13_2013_2300

#include <boost/spirit/repository/home/qi/numeric/detail/numeric_impl.hpp>
#include <boost/spirit/repository/home/support/unpack_map.hpp>
#include <boost/spirit/repository/home/support/numeric.hpp>
#include <boost/spirit/home/qi/detail/enable_lit.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/parser.hpp>

namespace boost { namespace spirit { namespace repository {
namespace tag {

template <typename T, typename Policy>
struct numeric_parser {
	BOOST_SPIRIT_IS_TAG()
};

}

namespace qi {

template <typename T, typename Policy>
struct numeric_parser : terminal<tag::numeric_parser<T, Policy>> {};

template <typename T, typename Policy>
struct any_numeric_parser : spirit::qi::primitive_parser<
	any_numeric_parser<T, Policy>
> {
	template <typename Context, typename Iterator>
	struct attribute {
		typedef T type;
	};

	template <typename Iterator, typename Context, typename Skipper>
	bool parse(
		Iterator &first, Iterator const &last, Context &ctx,
		Skipper const &skipper , T &attr_
	) const
	{
		typedef mpl::x11::apply_wrap<
			unpack_map<
				detail::numeric_impl,
				detail::trait_tag_order
			>, Policy
		> extract;

		spirit::qi::skip_over(first, last, skipper);
		return extract::parse(first, last, attr_);
	}

	template <
		typename Iterator, typename Context, typename Skipper,
		typename Attribute
	> bool parse(
		Iterator &first, Iterator const &last, Context &ctx,
		Skipper const &skipper, Attribute &attr_param
	) const
	{
		/* This case is called when Attribute is not T. */
		T attr_;
		if (parse(first, last, ctx, skipper, attr_)) {
			spirit::traits::assign_to(attr_, attr_param);
			return true;
		}
		return false;
	}

	template <typename Context>
	info what(Context &ctx) const
	{
		return info("numeric");
	}
};

template <typename T, typename Policy, bool no_attribute = true>
struct literal_numeric_parser : spirit::qi::primitive_parser<
	literal_numeric_parser<T, Policy, no_attribute>
> {
	template <typename Value>
	literal_numeric_parser(Value const& n) : n_(n) {}

	template <typename Context, typename Iterator>
	struct attribute : mpl::x11::if_c<no_attribute, unused_type, T> {};

	template <
		typename Iterator, typename Context, typename Skipper,
		typename Attribute
	> bool parse(
		Iterator &first, Iterator const &last, Context &ctx,
		Skipper const &skipper, Attribute &attr_param
	) const
	{
		typedef mpl::x11::apply_wrap<
			unpack_map<
				detail::numeric_impl,
				detail::trait_tag_order
			>, Policy
		> extract;
		spirit::qi::skip_over(first, last, skipper);
		Iterator save = first;
		T attr_;

		if (extract::parse(first, last, attr_)
		    && (attr_ == n_)) {
			spirit::traits::assign_to(attr_, attr_param);
			return true;
		}

		first = save;
		return false;
	}

	template <typename Context>
	info what(Context &ctx) const
	{
		return info("numeric");
	}

	T n_;
};

template <typename T, typename Policy>
struct make_numeric {
	typedef any_numeric_parser<T, Policy> result_type;

	result_type operator()(unused_type, unused_type) const
	{
		return result_type();
	}
};

template <typename T, typename Policy>
struct make_direct_numeric {
	typedef literal_numeric_parser<T, Policy, false> result_type;

	template <typename Terminal>
	result_type operator()(Terminal const &term, unused_type) const
	{
		return result_type(fusion::at_c<0>(term.args));
	}
};

template <typename T, typename Policy>
struct make_literal_numeric {
	typedef literal_numeric_parser<T, Policy> result_type;

	template <typename Terminal>
	result_type operator()(Terminal const& term, unused_type) const
	{
		return result_type(fusion::at_c<0>(term.args));
	}
};

}
}

/* Enables any numeric_parser */
template <typename T, typename Policy>
struct use_terminal<qi::domain, repository::tag::numeric_parser<T, Policy>>
: mpl::true_ {};

/* Enables any numeric_parser(n) */
template <typename T, typename Policy, typename A0>
struct use_terminal<
	qi::domain, terminal_ex<
		repository::tag::numeric_parser<T, Policy>,
		fusion::vector1<A0>
	>
> : mpl::true_ {};

/* Enables lazy numeric_parser(n) */
template <typename T, typename Policy>
struct use_lazy_terminal<
	qi::domain, repository::tag::numeric_parser<T, Policy>, 1
> : mpl::true_ {};

namespace qi {

template <typename T, typename Policy, typename Modifiers>
struct make_primitive<
	spirit::repository::tag::numeric_parser<T, Policy>, Modifiers
> : spirit::repository::qi::make_numeric<T, Policy> {};

template <typename T, typename Policy, typename A0, typename Modifiers>
struct make_primitive<
	terminal_ex<
		spirit::repository::tag::numeric_parser<T, Policy>,
		fusion::vector1<A0>
	>, Modifiers
> : spirit::repository::qi::make_direct_numeric<T, Policy> {};

}
}}

#endif
