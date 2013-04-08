/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_COMPARISON_APR_05_2013_1400)
#define MPL_X11_COMPARISON_APR_05_2013_1400

#include <boost/mpl/x11/numeric_cast.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct integral_c_tag {
	static const int value = 0;
};

template <typename T>
struct equal_to_tag {
	typedef typename T::tag type;
};

template <typename T, T v>
struct equal_to_tag<std::integral_constant<T, v>> {
	typedef integral_c_tag type;
};

template <typename T>
struct greater_tag {
	typedef typename T::tag type;
};

template <typename T, T v>
struct greater_tag<std::integral_constant<T, v>> {
	typedef integral_c_tag type;
};

template <typename T>
struct less_tag {
	typedef typename T::tag type;
};

template <typename T, T v>
struct less_tag<std::integral_constant<T, v>> {
	typedef integral_c_tag type;
};

template <typename Tag0, typename Tag1>
struct equal_to_impl
: if_c<
	(Tag0::value > Tag1::value),
	cast2nd_impl<equal_to_impl<Tag0, Tag0>, Tag0, Tag1>,
	cast1st_impl<equal_to_impl<Tag1, Tag1>, Tag0, Tag1>
>::type {};

template <>
struct equal_to_impl <integral_c_tag, integral_c_tag> {
	template <typename N0, typename N1>
	struct apply : bool_<(N0::value == N1::value)> {};
};

template <typename Tag0, typename Tag1>
struct greater_impl
: if_c<
	(Tag0::value > Tag1::value),
	cast2nd_impl<greater_impl<Tag0, Tag0>, Tag0, Tag1>,
	cast1st_impl<greater_impl<Tag1, Tag1>, Tag0, Tag1>
>::type {};

template <>
struct greater_impl <integral_c_tag, integral_c_tag> {
	template <typename N0, typename N1>
	struct apply : bool_<(N0::value > N1::value)> {};
};

template <typename Tag0, typename Tag1>
struct less_impl
: if_c<
	(Tag0::value > Tag1::value),
	cast2nd_impl<less_impl<Tag0, Tag0>, Tag0, Tag1>,
	cast1st_impl<less_impl<Tag1, Tag1>, Tag0, Tag1>
>::type {};

template <>
struct less_impl <integral_c_tag, integral_c_tag> {
	template <typename N0, typename N1>
	struct apply : bool_<(N0::value < N1::value)> {};
};

}

template <typename N0, typename N1>
struct equal_to : detail::equal_to_impl<
	typename detail::equal_to_tag<N0>::type,
	typename detail::equal_to_tag<N1>::type
>::template apply <N0, N1>::type {};

template <typename N0, typename N1>
struct greater : detail::greater_impl<
	typename detail::greater_tag<N0>::type,
	typename detail::greater_tag<N1>::type
>::template apply <N0, N1>::type {};

template <typename N0, typename N1>
struct less : detail::less_impl<
	typename detail::less_tag<N0>::type,
	typename detail::less_tag<N1>::type
>::template apply <N0, N1>::type {};

}}}

#endif
