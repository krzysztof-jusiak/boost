/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_MAKE_VALUE_MAY_10_2013_2300)
#define MPL_X11_MAKE_VALUE_MAY_10_2013_2300

#include <boost/mpl/x11/unpack_args.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename ValueType>
struct make_value_impl {
	template <typename...>
	struct apply;

	template <typename T0>
	struct apply<T0> {
		static ValueType &push_back(ValueType &v)
		{
			v.push_back(T0::value);
			return v;
		}
	};

	template <typename T0, typename... Tn>
	struct apply<T0, Tn...> {
		static ValueType &push_back(ValueType &v)
		{
			v.push_back(T0::value);
			return apply<Tn...>::push_back(v);
		}
	};
};

}

template <typename Sequence, typename ValueType>
ValueType &make_value(ValueType &in)
{
	typedef apply_wrap<
		x11::unpack_args<detail::make_value_impl<ValueType>>,
		Sequence
	> v;

	return v::push_back(in);
}

}}}

#endif
