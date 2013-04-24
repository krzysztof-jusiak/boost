/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_COMPARISON_APR_05_2013_1400)
#define MPL_X11_COMPARISON_APR_05_2013_1400

#include <boost/mpl/x11/numeric_cast.hpp>
#include <boost/mpl/x11/lambda_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename T>
struct equal_to_tag {
	typedef typename T::tag type;
};

template <typename T>
struct greater_tag {
	typedef typename T::tag type;
};

template <typename T>
struct greater_equal_tag {
	typedef typename T::tag type;
};

template <typename T>
struct less_tag {
	typedef typename T::tag type;
};

template <typename T>
struct less_equal_tag {
	typedef typename T::tag type;
};

template <typename T>
struct not_equal_to_tag {
	typedef typename T::tag type;
};

template <typename Tag0, typename Tag1>
struct equal_to_impl
: if_c<
	(Tag0::value > Tag1::value),
	cast2nd_impl<equal_to_impl<Tag0, Tag0>, Tag0, Tag1>,
	cast1st_impl<equal_to_impl<Tag1, Tag1>, Tag0, Tag1>
>::type {};

template <>
struct equal_to_impl<integral_c_tag, integral_c_tag> {
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
struct greater_impl<integral_c_tag, integral_c_tag> {
	template <typename N0, typename N1>
	struct apply : bool_<(N0::value > N1::value)> {};
};

template <typename Tag0, typename Tag1>
struct greater_equal_impl
: if_c<
	(Tag0::value > Tag1::value),
	cast2nd_impl<greater_equal_impl<Tag0, Tag0>, Tag0, Tag1>,
	cast1st_impl<greater_equal_impl<Tag1, Tag1>, Tag0, Tag1>
>::type {};

template <>
struct greater_equal_impl<integral_c_tag, integral_c_tag> {
	template <typename N0, typename N1>
	struct apply : bool_<(N0::value >= N1::value)> {};
};

template <typename Tag0, typename Tag1>
struct less_impl
: if_c<
	(Tag0::value > Tag1::value),
	cast2nd_impl<less_impl<Tag0, Tag0>, Tag0, Tag1>,
	cast1st_impl<less_impl<Tag1, Tag1>, Tag0, Tag1>
>::type {};

template <>
struct less_impl<integral_c_tag, integral_c_tag> {
	template <typename N0, typename N1>
	struct apply : bool_<(N0::value < N1::value)> {};
};

template <typename Tag0, typename Tag1>
struct less_equal_impl
: if_c<
	(Tag0::value > Tag1::value),
	cast2nd_impl<less_equal_impl<Tag0, Tag0>, Tag0, Tag1>,
	cast1st_impl<less_equal_impl<Tag1, Tag1>, Tag0, Tag1>
>::type {};

template <>
struct less_equal_impl<integral_c_tag, integral_c_tag> {
	template <typename N0, typename N1>
	struct apply : bool_<(N0::value <= N1::value)> {};
};

template <typename Tag0, typename Tag1>
struct not_equal_to_impl
: if_c<
	(Tag0::value > Tag1::value),
	cast2nd_impl<not_equal_to_impl<Tag0, Tag0>, Tag0, Tag1>,
	cast1st_impl<not_equal_to_impl<Tag1, Tag1>, Tag0, Tag1>
>::type {};

template <>
struct not_equal_to_impl<integral_c_tag, integral_c_tag> {
	template <typename N0, typename N1>
	struct apply : bool_<(N0::value != N1::value)> {};
};

}

template <typename...>
struct equal_to;

template <>
struct equal_to<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : equal_to<T0, T1> {};
};

template <typename Tag>
struct lambda<equal_to<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef equal_to<> result_;
	typedef equal_to<> type;
};

template <typename N0, typename N1>
struct equal_to<N0, N1> : detail::equal_to_impl<
	typename detail::equal_to_tag<N0>::type,
	typename detail::equal_to_tag<N1>::type
>::template apply <N0, N1>::type {};

template <typename...>
struct greater;

template <>
struct greater<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : greater<T0, T1> {};
};

template <typename Tag>
struct lambda<greater<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef greater<> result_;
	typedef greater<> type;
};

template <typename N0, typename N1>
struct greater<N0, N1> : detail::greater_impl<
	typename detail::greater_tag<N0>::type,
	typename detail::greater_tag<N1>::type
>::template apply <N0, N1>::type {};

template <typename...>
struct greater_equal;

template <>
struct greater_equal<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : greater_equal<T0, T1> {};
};

template <typename Tag>
struct lambda<greater_equal<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef greater_equal<> result_;
	typedef greater_equal<> type;
};

template <typename N0, typename N1>
struct greater_equal<N0, N1> : detail::greater_equal_impl<
	typename detail::greater_equal_tag<N0>::type,
	typename detail::greater_equal_tag<N1>::type
>::template apply <N0, N1>::type {};

template <typename...>
struct less;

template <>
struct less<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : less<T0, T1> {};
};

template <typename Tag>
struct lambda<less<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef less<> result_;
	typedef less<> type;
};

template <typename N0, typename N1>
struct less<N0, N1> : detail::less_impl<
	typename detail::less_tag<N0>::type,
	typename detail::less_tag<N1>::type
>::template apply <N0, N1>::type {};

template <typename...>
struct less_equal;

template <>
struct less_equal<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : less_equal<T0, T1> {};
};

template <typename Tag>
struct lambda<less_equal<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef less_equal<> result_;
	typedef less_equal<> type;
};

template <typename N0, typename N1>
struct less_equal<N0, N1> : detail::less_equal_impl<
	typename detail::less_equal_tag<N0>::type,
	typename detail::less_equal_tag<N1>::type
>::template apply <N0, N1>::type {};

template <typename...>
struct not_equal_to;

template <>
struct not_equal_to<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : not_equal_to<T0, T1> {};
};

template <typename Tag>
struct lambda<not_equal_to<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef not_equal_to<> result_;
	typedef not_equal_to<> type;
};

template <typename N0, typename N1>
struct not_equal_to<N0, N1> : detail::not_equal_to_impl<
	typename detail::not_equal_to_tag<N0>::type,
	typename detail::not_equal_to_tag<N1>::type
>::template apply <N0, N1>::type {};

}}}

#endif
