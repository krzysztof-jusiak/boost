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
		return result_type(CharValue::value);
	}
};

}
}

template <typename CharValue, typename CharEncoding>
struct use_terminal<
	qi::domain, repository::tag::static_char<CharValue, CharEncoding>
> : mpl::true_ {};

namespace qi {

template <typename CharValue, typename CharEncoding, typename Modifiers>
struct make_primitive<
	spirit::repository::tag::static_char<CharValue, CharEncoding>,
	Modifiers
> : spirit::repository::qi::make_static_char<CharValue, CharEncoding> {};

}
}}

#endif
