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

namespace boost { namespace spirit { namespace repository {

template <typename T>
struct value_wrapper {
	T value;

	operator T() const
	{
		return value;
	}
};

template <typename T>
value_wrapper<T> _r(T v)
{
	return value_wrapper<T>({v});
}

namespace qi { namespace detail {

template <typename T>
struct hex_integral {
	template <typename CharType>
	static T hex_digit(CharType in)
	{
		return T(
			(in & 0xf) + (in > CharType('9') ? 9 : 0)
		);
	}

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		static T const max((std::numeric_limits<T>::max)());
		static T const val(max >> 4);

		if (out > val)
			return false;

		out <<= 4;

		T digit(hex_digit(in));

		if (out > max - digit)
			return false;

		out += digit;
		return true;
	}

};

template <typename T, unsigned int Radix, bool Negative = false>
struct unchecked_small_radix_integral {
	typedef unchecked_small_radix_integral<
		T, Radix, !Negative
	> opposite_type;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		bool operator()(CharType in, T &out)
		{
			out = (out * Radix) + T(in & 0xf);
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		bool operator()(CharType in, T &out)
		{
			out = (out * Radix) - T(in & 0xf);
			return true;
		}
	};

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		return impl<CharType, Negative>()(in, out);
		return true;
	}

	BOOST_STATIC_ASSERT(Radix > 1 && Radix < 11);
};

template <typename T, unsigned int Radix, bool Negative = false>
struct unchecked_small_radix_fraction {
	typedef unchecked_small_radix_fraction<
		T, Radix, !Negative
	> opposite_type;

	T scale;
	unchecked_small_radix_integral<T, Radix, Negative> i;

	unchecked_small_radix_fraction()
	: scale(1) {}

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		if(i(in, out)) {
			scale *= Radix;
			return true;
		} else
			return false;
		
	}

	static bool adjust(unchecked_small_radix_fraction &self, T &out)
	{
		out /= self.scale;
		return true;
	}

	BOOST_STATIC_ASSERT(Radix > 1 && Radix < 11);
};

template <typename T, unsigned int Radix, bool Negative = false>
struct unchecked_small_radix_exponent {
	typedef unchecked_small_radix_exponent<
		T, Radix, !Negative
	> opposite_type;

	unsigned int last = 0;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		bool operator()(CharType in, T &out, unsigned int &last)
		{
			unsigned int digit(in & 0xf);
			unsigned int next = last * Radix + digit;

			out *= radix_pow<T, Radix>(next - last);
			last = next;
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		unsigned int last = 0;

		bool operator()(CharType in, T &out, unsigned int &last)
		{
			unsigned int digit(in & 0xf);
			unsigned int next = last * Radix + digit;

			out /= radix_pow<T, Radix>(next - last);
			last = next;
			return true;
		}
	};

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		return impl<CharType, Negative>()(in, out, last);
	}

	BOOST_STATIC_ASSERT(Radix > 1 && Radix < 11);
};

template <typename T, unsigned int Radix, int MaxDigits, bool Negative = false>
struct fixed_small_radix_integral {
	typedef fixed_small_radix_integral<
		T, Radix, MaxDigits, !Negative
	> opposite_type;

	int pos = 0;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		bool operator()(CharType in, T &out)
		{
			T digit(in & 0xf);
			out *= Radix;
			out += digit;
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		bool operator()(CharType in, T &out)
		{
			T digit(in & 0xf);
			out *= Radix;
			out -= digit;
			return true;
		}
	};

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		if (pos++ >= MaxDigits)
			return false;
		else
			return impl<CharType, Negative>()(in, out);
	}

	BOOST_STATIC_ASSERT(Radix > 1 && Radix < 11);
};

template <typename T, T Radix, bool Negative = false>
struct small_radix_integral {
	typedef small_radix_integral<T, Radix, !Negative> opposite_type;

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

	BOOST_STATIC_ASSERT(Radix > 1 && Radix < 11);
};

template <unsigned int...>
struct length_filter;

template <unsigned int MinDigits>
struct length_filter<MinDigits> {
	unsigned int pos;

	length_filter()
	: pos(0) {}

	template <typename Iterator>
	bool operator()(Iterator &first, Iterator const &last, int count)
	{
		if (count > 0) {
			pos += count;
			return pos >= MinDigits;
		} else
			return true;
		
	}
};

template <unsigned int MinDigits, unsigned int MaxDigits>
struct length_filter<MinDigits, MaxDigits> {
	unsigned int pos;

	length_filter()
	: pos(0) {}

	template <typename Iterator>
	bool operator()(Iterator &first, Iterator const &last, int count)
	{
		if (count > 0) {
			pos += count;
			return (pos >= MinDigits) && (pos <= MaxDigits);
		} else
			return true;
		
	}
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

template <typename CharType>
using default_fractional_separator = static_char<
	mpl::x11::integral_constant<CharType, '.'>
>;

template <typename CharType>
using default_exponent_separator = static_variant<
	mpl::x11::pair<
		static_char<mpl::x11::integral_constant<CharType, 'e'>>,
		mpl::x11::true_type
	>,
	mpl::x11::pair<
		static_char<mpl::x11::integral_constant<CharType, 'E'>>,
		mpl::x11::true_type
	>
>;


}}
}}}

#endif
