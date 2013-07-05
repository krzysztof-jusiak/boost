/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815)
#define SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_utils.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename T>
struct decimal_real_wrapper {
	typedef decimal_real_wrapper<T> wrapper_type;

	multiprecision::number<multiprecision::cpp_int_backend<>> mantissa;
	int exponent;

	decimal_real_wrapper()
	: mantissa(0), exponent(0)
	{}

	template <typename CharType, bool Negative_ = false>
	struct impl {
		static bool mantissa_op(CharType in, wrapper_type &out)
		{
			out.mantissa *= 10;
			out.mantissa += ascii_digit_value<10>(in);
			return true;
		}

		static bool exponent_op(CharType in, wrapper_type &out)
		{
			out.exponent *= 10;
			out.exponent += ascii_digit_value<10>(in);
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		static bool mantissa_op(CharType in, wrapper_type &out)
		{
			out.mantissa *= 10;
			out.mantissa -= ascii_digit_value<10>(in);
			return true;
		}

		static bool exponent_op(CharType in, wrapper_type &out)
		{
			out.exponent *= 10;
			out.exponent -= ascii_digit_value<10>(in);
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
			>::mantissa_op(in, out);
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
				out.exponent++;

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
	static double const tinytens[] = {
		1e-16, 1e-32, 1e-64, 1e-128,
		9007199254740992.0 * 9007199254740992.0e-256
	};

	return mantissa.template convert_to<double>();
}

}
}}}}

#endif


