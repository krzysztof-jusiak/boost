/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_STATIC_VARIANT_MAY_18_2013_1930)
#define SPIRIT_REPOSITORY_QI_STATIC_VARIANT_MAY_18_2013_1930

namespace boost { namespace spirit { namespace repository {
namespace tag {

template <typename... Parser>
struct static_variant {
        BOOST_SPIRIT_IS_TAG()
};

}

namespace qi {

template <typename... Parser>
struct static_variant : terminal<tag::static_variant<Parser...>> {};

template <long Index, typename... Pn>
struct static_variant_parser;

template <long Index, typename P0>
struct static_variant_parser<Index, P0> : spirit::qi::primitive_parser<
	static_variant_parser<Index, P0>
> {
	template <typename Context, typename Iterator>
	struct attribute {
		typedef long type;
	};

	template <
		typename Iterator, typename Context, typename Skipper,
		typename Attribute
	>
	bool parse(
		Iterator &first, Iterator const &last, Context &ctx,
		Skipper const &skipper , Attribute &attr_
	) const
	{
		Iterator iter(first);
		spirit::qi::skip_over(iter, last, skipper);

		P0 p;

		if (spirit::qi::parse(iter, last, p)) {
			first = iter;
			spirit::traits::assign_to(Index, attr_);
			return true;
		} else
			return false;
	}

	template <typename Context>
	info what(Context &ctx) const
	{
		return info("static_variant");
	}
};

template <long Index, typename P0, typename... Pn>
struct static_variant_parser<Index, P0, Pn...> : spirit::qi::primitive_parser<
	static_variant_parser<Index, P0, Pn...>
> {
	template <typename Context, typename Iterator>
	struct attribute {
		typedef long type;
	};

	 template <
		typename Iterator, typename Context, typename Skipper,
		typename Attribute
	> bool parse(
		Iterator &first, Iterator const &last, Context &ctx,
		Skipper const &skipper, Attribute &attr_
	) const
	{
		Iterator iter(first);
		spirit::qi::skip_over(iter, last, skipper);

		P0 p;

		if (spirit::qi::parse(iter, last, p)) {
			first = iter;
			spirit::traits::assign_to(Index, attr_);
			return true;
		} else {
			static_variant_parser<Index + 1, Pn...> pn;
			return pn.parse(first, last, ctx, skipper, attr_);
		}
	}

	template <typename Context>
	info what(Context &ctx) const
	{
		return info("static_variant");
	}
};

template <typename... Parser>
struct make_static_variant {
	typedef static_variant_parser<0, Parser...> result_type;

	result_type operator()(unused_type, unused_type) const
        {
		return result_type();
	}
};
}
}

template <typename... Parser>
struct use_terminal<
	qi::domain, repository::tag::static_variant<Parser...>
> : mpl::true_ {};

namespace qi {

template <typename... Parser>
struct make_primitive<
	spirit::repository::tag::static_variant<Parser...>,
	Modifiers
> : spirit::repository::qi::make_static_variant<Parser...> {};

}
}}
