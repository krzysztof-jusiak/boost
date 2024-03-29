/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_STATIC_CHAR_MAY_22_2013_2300)
#define SPIRIT_REPOSITORY_QI_STATIC_CHAR_MAY_22_2013_2300

#include <boost/spirit/home/qi/char/char.hpp>

namespace boost { namespace spirit { namespace repository {
namespace tag {

template <typename CharValue, typename CharEncoding>
struct static_char {
        BOOST_SPIRIT_IS_TAG()
};

template <typename CharFrom, typename CharTo, typename CharEncoding>
struct static_char_range {
        BOOST_SPIRIT_IS_TAG()
};

}

namespace qi {

template <
	typename CharValue,
	typename CharEncoding = spirit::char_encoding::standard
>
struct static_char : terminal<tag::static_char<CharValue, CharEncoding>> {};

template <typename CharValue, typename CharEncoding>
struct make_static_char {
	typedef typename CharEncoding::char_type char_type;

	typedef typename spirit::qi::literal_char<
		CharEncoding, false, false
	> result_type;

	result_type operator()(unused_type, unused_type) const
        {
		return p;
	}

private:
	static result_type const p;
};

template <typename CharValue, typename CharEncoding>
typename make_static_char<CharValue, CharEncoding>::result_type const
make_static_char<CharValue, CharEncoding>::p = CharValue::value;

template <
	typename CharFrom, typename CharTo,
	typename CharEncoding = spirit::char_encoding::standard
>
struct static_char_range : terminal<
	tag::static_char_range<CharFrom, CharTo, CharEncoding>
> {};

template <typename CharFrom, typename CharTo, typename CharEncoding>
struct make_static_char_range {
	typedef typename CharEncoding::char_type char_type;

	typedef typename spirit::qi::char_range<
		CharEncoding, false
	> result_type;

	result_type operator()(unused_type, unused_type) const
        {
		return p;
	}

private:
	struct make_p {
		result_type p;

		make_p()
		: p(CharFrom::value, CharTo::value)
		{}
	};

	static result_type const p;
};

template <typename CharFrom, typename CharTo, typename CharEncoding>
typename make_static_char_range<CharFrom, CharTo, CharEncoding>::result_type const
make_static_char_range<CharFrom, CharTo, CharEncoding>::p
= make_static_char_range::make_p().p;

}
}

template <typename CharValue, typename CharEncoding>
struct use_terminal<
	qi::domain, repository::tag::static_char<CharValue, CharEncoding>
> : mpl::true_ {};

template <typename CharFrom, typename CharTo, typename CharEncoding>
struct use_terminal<
	qi::domain, repository::tag::static_char_range<
		CharFrom, CharTo, CharEncoding
	>
> : mpl::true_ {};

namespace qi {

template <typename CharValue, typename CharEncoding, typename Modifiers>
struct make_primitive<
	spirit::repository::tag::static_char<CharValue, CharEncoding>,
	Modifiers
> : spirit::repository::qi::make_static_char<CharValue, CharEncoding> {};

template <
	typename CharFrom, typename CharTo, typename CharEncoding,
	typename Modifiers
> struct make_primitive<
	spirit::repository::tag::static_char_range<
		CharFrom, CharTo, CharEncoding
	>, Modifiers
> : spirit::repository::qi::make_static_char_range<
	CharFrom, CharTo, CharEncoding
> {};

}
}}

#endif
