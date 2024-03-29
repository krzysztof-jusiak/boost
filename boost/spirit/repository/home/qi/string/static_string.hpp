/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_STATIC_STRING_MAY_11_2013_2300)
#define SPIRIT_REPOSITORY_QI_STATIC_STRING_MAY_11_2013_2300

#include <boost/mpl/x11/make_value.hpp>
#include <boost/spirit/home/qi/string/lit.hpp>

namespace boost { namespace spirit { namespace repository {
namespace tag {

template <typename Sequence, typename CharEncoding>
struct static_string {
        BOOST_SPIRIT_IS_TAG()
};

}

namespace qi {

template <
	typename Sequence,
	typename CharEncoding = spirit::char_encoding::standard
>
struct static_string : terminal<tag::static_string<Sequence, CharEncoding>> {};

template <typename Sequence, typename CharEncoding>
struct make_static_string {
	typedef typename CharEncoding::char_type char_type;
	typedef typename spirit::qi::literal_string<
		std::basic_string<char_type>, false
	> result_type;

	result_type operator()(unused_type, unused_type) const
        {
		return p;
	}

private:
	struct make_p {
		std::basic_string<char_type> str;
		result_type p;

		make_p()
		: p(mpl::x11::make_value<Sequence>(str))
		{}
	};

	static result_type const p;
};

template <typename Sequence, typename CharEncoding>
typename make_static_string<Sequence, CharEncoding>::result_type const
make_static_string<Sequence, CharEncoding>::p = make_static_string::make_p().p;

}
}

template <typename Sequence, typename CharEncoding>
struct use_terminal<
	qi::domain, repository::tag::static_string<Sequence, CharEncoding>
> : mpl::true_ {};

namespace qi {

template <typename Sequence, typename CharEncoding, typename Modifiers>
struct make_primitive<
	spirit::repository::tag::static_string<Sequence, CharEncoding>,
	Modifiers
> : spirit::repository::qi::make_static_string<Sequence, CharEncoding> {};

}
}}

#endif
