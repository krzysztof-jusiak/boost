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
#include <boost/any.hpp>
#include <boost/spirit/repository/home/qi/char/static_char.hpp>
#include <boost/spirit/repository/home/qi/string/static_symbols.hpp>
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

template <unsigned int Radix, typename Char>
inline static Char ascii_digit_value(Char ch)
{
	if (Radix <= 10 || (ch >= '0' && ch <= '9'))
		return ch - '0';

	return spirit::char_encoding::ascii::tolower(ch) - 'a' + 10;
}

template <typename T, unsigned int Radix, bool Negative = false>
struct unchecked_ascii_integer {
	typedef unchecked_ascii_integer<
		T, Radix, !Negative
	> opposite_type;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		bool operator()(CharType in, T &out)
		{
			out = (out * Radix) + T(ascii_digit_value<Radix>(in));
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		bool operator()(CharType in, T &out)
		{
			out = (out * Radix) - T(ascii_digit_value<Radix>(in));
			return true;
		}
	};

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		return impl<CharType, Negative>()(in, out);
	}

	BOOST_STATIC_ASSERT(Radix > 1 && Radix < 37);
};

template <typename T, unsigned int Radix, bool Negative = false>
struct unchecked_ascii_fraction {
	typedef unchecked_ascii_fraction<
		T, Radix, !Negative
	> opposite_type;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		bool operator()(CharType in, T &out, T &scale)
		{
			out = out + T(ascii_digit_value<10>(in)) * scale;
			scale /= Radix;
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		bool operator()(CharType in, T &out, T &scale)
		{
			out = out - T(ascii_digit_value<10>(in)) * scale;
			scale /= Radix;
			return true;
		}
	};

	T scale;

	unchecked_ascii_fraction()
	: scale(T(1) / Radix) {}

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		return impl<CharType, Negative>()(in, out, scale);
	}

	BOOST_STATIC_ASSERT(Radix > 1 && Radix < 37);
};

template <typename T, unsigned int Radix, bool Negative = false>
struct unchecked_ascii_exponent {
	typedef unchecked_ascii_exponent<
		T, Radix, !Negative
	> opposite_type;

	double last;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		bool operator()(CharType in, T &out, double &last)
		{
			unsigned int digit(ascii_digit_value<Radix>(in));
			double next = last * Radix + digit;

			out *= exp10(next - last);
			last = next;
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		bool operator()(CharType in, T &out, double &last)
		{
			unsigned int digit(ascii_digit_value<Radix>(in));
			double next = last * Radix + digit;

			out /= exp10(next - last);
			last = next;
			return true;
		}
	};

	unchecked_ascii_exponent()
	: last(0)
	{}

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		return impl<CharType, Negative>()(in, out, last);
	}

	static_assert(
		Radix > 1 && Radix < 37,
		"Unsupported radix value (must be between 2 and 36)"
	);
};

template <typename T, unsigned int Radix, int MaxDigits, bool Negative = false>
struct fixed_ascii_integer {
	typedef fixed_ascii_integer<
		T, Radix, MaxDigits, !Negative
	> opposite_type;

	int pos = 0;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		bool operator()(CharType in, T &out)
		{
			T digit(ascii_digit_value<Radix>(in));
			out *= Radix;
			out += digit;
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		bool operator()(CharType in, T &out)
		{
			T digit(ascii_digit_value<Radix>(in));
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

	static_assert(
		Radix > 1 && Radix < 37,
		"Unsupported radix value (must be between 2 and 36)"
	);
};

template <typename T, T Radix, bool Negative = false>
struct ascii_integer {
	typedef ascii_integer<T, Radix, !Negative> opposite_type;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		bool operator()(CharType in, T &out)
		{
			constexpr T const max((std::numeric_limits<T>::max)());
			constexpr T const val(max / Radix);

			T digit(ascii_digit_value<Radix>(in));

			if (
				(out > val)
				|| ((out * Radix) > (max - digit))
			)
				return false;

			out = out * Radix + digit;
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		bool operator()(CharType in, T &out)
		{
			constexpr T const min((std::numeric_limits<T>::min)());
			constexpr T const val((min + 1) / Radix);

			T digit(ascii_digit_value<Radix>(in));

			if (
				(out < val)
				|| ((out * Radix) < (min + digit))
			)
				return false;

			out = out * Radix - digit;
			return true;
		}
	};

	template <typename CharType>
	bool operator()(CharType in, T &out)
	{
		return impl<CharType, Negative>()(in, out);
	}

	static_assert(
		Radix > 1 && Radix < 37,
		"Unsupported radix value (must be between 2 and 36)"
	);
};

template <unsigned int...>
struct length_filter;

template <unsigned int MinDigits>
struct length_filter<MinDigits> {
	boost::any last_pos;

	template <typename Iterator>
	bool pre(Iterator const &iter)
	{
		last_pos = iter;
		return true;
	}

	template <typename Iterator>
	bool post(Iterator const &iter)
	{
		auto last_iter(boost::any_cast<Iterator>(last_pos));
		return (iter - last_iter) >= MinDigits;
	}

	template <typename Iterator>
	bool operator()(Iterator &first, Iterator const &last)
	{
		return false;
	}
};

template <unsigned int MinDigits, unsigned int MaxDigits>
struct length_filter<MinDigits, MaxDigits> {
	boost::any last_pos;

	template <typename Iterator>
	bool pre(Iterator const &iter)
	{
		last_pos = iter;
		return true;
	}

	template <typename Iterator>
	bool post(Iterator &iter)
	{
		auto last_iter(boost::any_cast<Iterator>(last_pos));
		auto count(iter - last_iter);
		return (count >= MinDigits) && (count <= MaxDigits);
	}

	template <typename Iterator>
	bool operator()(Iterator &first, Iterator const &last)
	{
		return false;
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

template <typename T>
struct inf_value_wrapper {
	typedef std::function<T (bool)> value_type;

	virtual T operator()(bool neg)
	{
		return neg ? -std::numeric_limits<T>::infinity()
			   : std::numeric_limits<T>::infinity();
	}
};

template <typename T>
struct nan_value_wrapper {
	typedef std::function<T (bool)> value_type;

	T operator()(bool neg)
	{
		return neg ? -std::numeric_limits<T>::quiet_NaN()
			   : std::numeric_limits<T>::quiet_NaN();
	}
};


template <typename T, typename CharType>
using default_fp_special_values = static_symbols<
	mpl::x11::map<
		mpl::x11::pair<
			mpl::x11::list_c<CharType, 'i', 'n', 'f'>,
			inf_value_wrapper<T>
		>,
		mpl::x11::pair<
			mpl::x11::list_c<CharType, 'I', 'N', 'F'>,
			inf_value_wrapper<T>
		>,
		mpl::x11::pair<
			mpl::x11::list_c<
				CharType,
				'i', 'n', 'f', 'i', 'n', 'i', 't', 'y'
			>, inf_value_wrapper<T>
		>,
		mpl::x11::pair<
			mpl::x11::list_c<
				CharType,
				'I', 'N', 'F', 'I', 'N', 'I', 'T', 'Y'
			>, inf_value_wrapper<T>
		>,
		mpl::x11::pair<
			mpl::x11::list_c<CharType, 'n', 'a', 'n'>,
			nan_value_wrapper<T>
		>,
		mpl::x11::pair<
			mpl::x11::list_c<CharType, 'N', 'A', 'N'>,
			nan_value_wrapper<T>
		>,
		mpl::x11::pair<
			mpl::x11::list_c<
				CharType,
				'n', 'a', 'n', '(', '.', '.', '.', ')'
			>, nan_value_wrapper<T>
		>
	>, CharType
>;

}}
}}}

#endif
