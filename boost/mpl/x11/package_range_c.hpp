/*==============================================================================
    Copyright (c) 2009      Larry Evans
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_PACKAGE_RANGE_C_APR_30_2013_1830)
#define MPL_X11_PACKAGE_RANGE_C_APR_30_2013_1830

#include <boost/mpl/x11/package.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Tpack, typename Tint>
struct package_range_forward;

template <typename T, T... Cn, T Cbegin, T Cend>
struct package_range_forward<
	package_c<T, Cn...>, package_c<T, Cbegin, Cend>
> : package_range_forward<
	package_c<T, Cend, Cn...>, package_c<T, Cbegin, T(Cend - 1)>
> {};

template <typename T, T... Cn, T Cbegin>
struct package_range_forward<
	package_c<T, Cn...>, package_c<T, Cbegin, Cbegin>
> {
	typedef package_c<T, Cbegin, Cn...> type;
};

template <typename Tpack, typename Tint>
struct package_range_backward;

template <typename T, T... Cn, T Cbegin, T Cend>
struct package_range_backward<
	package_c<T, Cn...>, package_c<T, Cbegin, Cend>
> : package_range_backward<
	package_c<T, Cn..., Cend>, package_c<T, Cbegin, T(Cend - 1)>
> {};

template <typename T, T... Cn, T Cbegin>
struct package_range_backward<
	package_c<T, Cn...>, package_c<T, Cbegin, Cbegin>
> {
	typedef package_c<T, Cn..., Cbegin> type;
};

}

template <typename T, T Cbegin, T Cend>
struct package_range_c : eval_if_c<
	(Cbegin == Cend), package_c<T>,
	eval_if_c<
		(Cbegin < Cend), detail::package_range_forward<
			package_c<T>, package_c<T, Cbegin, T(Cend - 1)>
		>,
		detail::package_range_backward<
			package_c<T>, package_c<T, Cend, T(Cbegin - 1)>
		>
	>
> {};

}}}

#endif
