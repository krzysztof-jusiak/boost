/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Based on the implementation by:
        Rob Pike and Ken Thompson.
        Copyright (c) 2002 by Lucent Technologies.

            Permission to use, copy, modify, and distribute this software for
            any purpose without fee is hereby granted, provided that this
            entire notice is included in all copies of any software which is or
            includes a copy or modification of this software and in all copies
            of the supporting documentation for such software.

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815)
#define SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815

#include <boost/multiprecission/cpp_int.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_utils.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename T>
struct decimal_real_wrapper {
	typedef decimal_real_wrapper<T> wrapper_type;

	multiprecission::number<cpp_int_backend<>> mantissa;
	int exponent;

	decimal_real_wrapper()
	: mantissa(0), exponent(0), flags(0)
	{}

	template <typename CharType, bool Negative_ = false>
	struct impl {
		static bool mantissa_op(CharType in, wrapper_type &out)
		{
			out.mantissa
			+= out.mantissa * 10 + ascii_digit_value<10>(in);
			return true;
		}

		static bool exponent_op(CharType in, wrapper_type &out)
		{
			out.exponent
			+= out.exponent * 10 + ascii_digit_value<10>(in);
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		static bool mantissa_op(CharType in, wrapper_type &out)
		{
			out.mantissa
			+= out.mantissa * 10 - ascii_digit_value<10>(in);
			return true;
		}

		static bool exponent_op(CharType in, wrapper_type &out)
		{
			out.exponent
			+= out.exponent * 10 - ascii_digit_value<10>(in);
			return true;
		}
	};

	template <bool Negative = false>
	struct integer_op {
		typedef integer_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			return wrapper_type::impl<
				CharType, Negative
			>::integer_op(in, out);
		}
	};

	template <bool Negative = false>
	struct fraction_op {
		typedef fraction_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			bool rv(wrapper_type::impl<
				CharType, Negative
			>::mantissa_op(in, out));
			if (rv)
				out.exponent--;

			return rv;
		}
	};

	template <bool Negative = false>
	struct exponent_op {
		typedef exponent_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			return wrapper_type::impl<
				CharType, Negative
			>::exponent_op(in, out);
		}
	};

	operator T() const;
};

template <>
decimal_real_wrapper<double>::operator double() const
{


	return mantissa.template convert_to<double>();
}

}
}}}}

#endif


