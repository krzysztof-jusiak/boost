/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011      Bryce Lelbach
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_MAR_13_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_MAR_13_2013_2300

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/detail/enable_lit.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/repository/home/support/numeric.hpp>
#include <boost/spirit/repository/home/qi/numeric/detail/numeric_impl.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi
{

template <typename T, typename Policy>
struct numeric_parser
: boost::spirit::qi::primitive_parser<numeric_parser<T, Policy> > {
	template <typename Context, typename Iterator>
	struct attribute {
		typedef T type;
	};

	template <typename Iterator, typename Context, typename Skipper>
	bool parse(
		Iterator& first, Iterator const& last, Context& /*context*/,
		Skipper const& skipper , T& attr_
	) const
	{
		typedef detail::numeric_impl<T, Policy> extract;
		boost::spirit::qi::skip_over(first, last, skipper);
		return extract::parse(first, last, attr_, Policy());
	}

	template <
		typename Iterator, typename Context, typename Skipper,
		typename Attribute
	> bool parse(
		Iterator& first, Iterator const& last, Context& context,
		Skipper const& skipper, Attribute& attr_param
	) const
	{
		// this case is called when Attribute is not T
		T attr_;
		if (parse(first, last, context, skipper, attr_)) {
			traits::assign_to(attr_, attr_param);
			return true;
		}
		return false;
	}

	template <typename Context>
	info what(Context& /*context*/) const
	{
		return info("numeric");
	}
};

template <typename T, typename Policy, bool no_attribute = true>
struct literal_numeric_parser
: boost::spirit::qi::primitive_parser<
	literal_numeric_parser<T, Policy, no_attribute>
> {
	template <typename Value>
	literal_numeric_parser(Value const& n) : n_(n) {}

	template <typename Context, typename Iterator>
	struct attribute : mpl::if_c<no_attribute, unused_type, T> {};

	template <
		typename Iterator, typename Context, typename Skipper,
		typename Attribute
	> bool parse(
		Iterator& first, Iterator const& last, Context&,
		Skipper const& skipper, Attribute& attr_param
	) const
	{
		typedef detail::numeric_impl<T, Policy> extract;
		boost::spirit::qi::skip_over(first, last, skipper);
		Iterator save = first;
		T attr_;

		if (extract::parse(first, last, attr_, Policy())
		    && (attr_ == n_)) {
			traits::assign_to(attr_, attr_param);
			return true;
		}

		first = save;
		return false;
	}

	template <typename Context>
	info what(Context& /*context*/) const
	{
		return info("numeric");
	}

	T n_;
};


}}}}

#endif
