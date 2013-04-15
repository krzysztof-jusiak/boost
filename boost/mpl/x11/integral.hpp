/*=============================================================================
    Copyright (c) 2000-2006 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_INTEGRAL_APR_02_2013_1615)
#define MPL_X11_INTEGRAL_APR_02_2013_1615

#include <type_traits>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct integral_c_tag {
	static const int value = 0;
};

}

template <typename T, T v>
struct integral_constant : std::integral_constant<T, v> {
	typedef integral_constant type;
	typedef detail::integral_c_tag tag;
	typedef integral_constant<T, static_cast<T>((v + 1))> next;
	typedef integral_constant<T, static_cast<T>((v - 1))> prior;
};

template <bool value>
using bool_ = integral_constant<bool, value>;

typedef bool_<false> false_type;
typedef bool_<true> true_type;

template <char value>
using char_ = integral_constant<char, value>;

template <int value>
using int_ = integral_constant<int, value>;

template <long value>
using long_ = integral_constant<long, value>;

}}}

#endif
