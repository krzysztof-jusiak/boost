/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815)
#define SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815

#include <boost/spirit/repository/home/qi/numeric/numeric_utils.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <
	typename T, unsigned int RadixM, unsigned int RadixE = RadixM,
	unsigned int ExponentBase = RadixM
> struct real_wrapper {
	typedef real_wrapper<T, RadixM, RadixE> wrapper_type;

	T mantissa;
	short scale;
	short exponent;

	template <typename CharType, bool Negative_ = false>
	struct impl {
		static bool integral_op(CharType in, wrapper_type &out)
		{
			out.mantissa *= RadixM;
			out.mantissa += ascii_digit_value<RadixM>(in);
			return true;
		}

		static bool exponent_op(CharType in, wrapper_type &out)
		{
			out.exponent *= RadixE;
			out.exponent += ascii_digit_value<RadixE>(in);
			return true;
		}
	};

	template <typename CharType>
	struct impl<CharType, true> {
		static bool integral_op(CharType in, wrapper_type &out)
		{
			out.mantissa *= RadixM;
			out.mantissa -= ascii_digit_value<RadixM>(in);
			return true;
		}

		static bool exponent_op(CharType in, wrapper_type &out)
		{
			out.exponent *= RadixE;
			out.exponent -= ascii_digit_value<RadixE>(in);
			return true;
		}
	};

	template <bool Negative = false>
	struct integral_op {
		typedef integral_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			return impl<CharType, Negative>::integral_op(in, out);
		}
	};

	template <bool Negative = false>
	struct fractional_op {
		typedef fractional_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			bool rv(impl<CharType, Negative>::integral_op(in, out));
			if (rv)
				out.scale++;

			return rv;
		}
	};

	template <bool Negative = false>
	struct exponent_op {
		typedef exponent_op<!Negative> opposite_type;

		template <typename CharType>
		bool operator()(CharType in, wrapper_type &out)
		{
			return impl<CharType, Negative>::exponent_op(in, out);
		}
	};

	real_wrapper()
	: mantissa(traits::zero<T>()), scale(0), exponent(0)
	{}

	operator T() const;
};

template <>
real_wrapper<double, 10, 10, 10>::operator double() const
{
	double m(pow10(double(exponent - scale)));


	return mantissa * m;
}

}
}}}}

#endif


