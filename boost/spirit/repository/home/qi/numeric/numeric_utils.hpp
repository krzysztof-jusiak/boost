/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Partially derived from original Boost::Spirit implementation:
	Copyright (c) 2001-2011 Joel de Guzman
	Copyright (c) 2001-2011 Hartmut Kaiser
	Copyright (c) 2011 Jan Frederick Eick
	Copyright (c) 2011 Christopher Jefferson
	Copyright (c) 2006 Stephen Nutt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_UTILS_MAY_26_2013_2000)
#define SPIRIT_REPOSITORY_QI_NUMERIC_UTILS_MAY_26_2013_2000

#include <limits>
#include <boost/static_assert.hpp>
#include <boost/spirit/repository/home/qi/char/static_char.hpp>
#include <boost/spirit/repository/home/qi/auxiliary/static_variant.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename T, int Radix, bool Negative = false>
struct small_radix_inserter {
	typedef small_radix_inserter<T, Radix, !Negative> opposite_inserter;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		bool operator()(CharType in, T &out)
		{
			static T const max((std::numeric_limits<T>::max)());
			static T const val(max / Radix);

			if (out > val)
				return false;

			out *= Radix;

			T digit(in & 0xf);

			if (out > max - digit)
				return false;

			out += digit;
				return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		bool operator()(CharType in, T &out)
		{
			static T const min((std::numeric_limits<T>::min)());
			static T const val((min + 1) / Radix);

			if (out < val)
				return false;

			out *= Radix;

			T digit(in & 0xf);

			if (out < min + digit)
				return false;

			out -= digit;
			return true;
		}
	};

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		return impl<CharType, Negative>()(in, out);
	}

	BOOST_STATIC_ASSERT(Radix > 1);
	BOOST_STATIC_ASSERT(Radix < 11);
};

template <typename CharType>
using default_sign = static_variant<
	mpl::x11::pair<
		static_char<mpl::x11::integral_constant<CharType, '-'>>,
		mpl::x11::true_type
	>,
	mpl::x11::pair<
		static_char<mpl::x11::integral_constant<CharType, '+'>>,
		mpl::x11::false_type
	>
>;

}
}}}}

#endif
