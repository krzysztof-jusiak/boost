/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_STATIC_SYMBOLS_SEP_09_2013_1230)
#define SPIRIT_REPOSITORY_QI_STATIC_SYMBOLS_SEP_09_2013_1230

#include <boost/mpl/x11/for_each.hpp>
#include <boost/mpl/x11/front_back.hpp>
#include <boost/mpl/x11/make_value.hpp>
#include <boost/mpl/x11/key_value_type.hpp>
#include <boost/spirit/home/qi/string/symbols.hpp>

namespace boost { namespace spirit { namespace repository {
namespace tag {

template <typename Map, typename CharEncoding>
struct static_symbols {
        BOOST_SPIRIT_IS_TAG()
};

}

namespace qi {

template <
	typename Map,
	typename CharType = spirit::char_encoding::standard::char_type
>
struct static_symbols : terminal<tag::static_symbols<Map, CharType>> {};

template <typename Map, typename CharType>
struct make_static_symbols {
	typedef CharType char_type;
	typedef typename spirit::qi::symbols<
		char_type, typename mpl::x11::value_type<
			Map, typename mpl::x11::front<Map>::type
		>::type::value_type
	> result_type;

	result_type operator()(unused_type, unused_type) const
        {
		return p;
	}

private:
	struct make_p {
		result_type p;

		make_p()
		{
			mpl::x11::for_each<Map>(*this);
		}

		template <typename P>
		void operator()(P px)
		{
			std::basic_string<char_type> str_key;
			typename mpl::x11::second<P>::type val;
			mpl::x11::make_value<
				typename mpl::x11::first<P>::type
			>(str_key);

			p.add(str_key, val);
		}
	};

	static result_type const p;
};

template <typename Map, typename CharType>
typename make_static_symbols<Map, CharType>::result_type const
make_static_symbols<Map, CharType>::p = make_static_symbols::make_p().p;

}
}

template <typename Map, typename CharType>
struct use_terminal<
	qi::domain, repository::tag::static_symbols<Map, CharType>
> : mpl::true_ {};

namespace qi {

template <typename Map, typename CharType, typename Modifiers>
struct make_primitive<
	spirit::repository::tag::static_symbols<Map, CharType>,
	Modifiers
> : spirit::repository::qi::make_static_symbols<Map, CharType> {};

}
}}

#endif
