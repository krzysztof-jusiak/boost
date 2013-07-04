/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815)
#define SPIRIT_REPOSITORY_QI_REAL_WRAPPER_JUL_3_2013_1815

#include <boost/multiprecision/mpfr.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_utils.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename T>
struct decimal_real_wrapper {
	typedef decimal_real_wrapper<T> wrapper_type;

	multiprecision::number<multiprecision::mpfr_float_backend<
		//std::numeric_limits<T>::digits10
		0
	>> value;

	decimal_real_wrapper()
	: value(traits::zero<T>())
	{}

	template <typename NumType>
	decimal_real_wrapper(NumType v)
	: value(v)
	{}

	template <typename NumType>
	decimal_real_wrapper &operator*=(NumType v)
	{
		value *= v;
		return *this;
	}

	template <typename NumType>
	decimal_real_wrapper &operator/=(NumType v)
	{
		value /= v;
		return *this;
	}

	operator T() const
	{
		return value.template convert_to<T>();
	}
};

}
}}}}

#endif


