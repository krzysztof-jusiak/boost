/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_VECTOR_APR_10_2013_2330)
#define MPL_X11_VECTOR_APR_10_2013_2330

#include <boost/mpl/x11/detail/type_wrapper.hpp>
#include <boost/mpl/x11/void.hpp>
#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/arithmetic.hpp>
#include <boost/mpl/x11/iterator_tags.hpp>

#include <boost/mpl/x11/detail/at.hpp>
#include <boost/mpl/x11/detail/clear.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct vector_tag;

struct vector_iterator_tag;

template <typename T, typename Base, bool at_front = false>
struct v_item : Base {
	typedef typename Base::upper_bound_ index_;
	typedef typename increment<index_>::type upper_bound_;
	typedef typename increment<typename Base::size>::type size;
	typedef Base base;
	typedef v_item type;

	static type_wrapper<T> item_(index_);
	using Base::item_;
};

template <typename T, typename Base>
struct v_item<T, Base, true> : Base {
	typedef typename decrement<typename Base::lower_bound_>::type index_;
	typedef index_ lower_bound_;
	typedef typename increment<typename Base::size>::type size;
	typedef Base base;
	typedef v_item type;

	static type_wrapper<T> item_(index_);
	using Base::item_;
};

template <typename Base, bool at_front>
struct v_mask : Base {
	typedef typename decrement<typename Base::upper_bound_>::type index_;
	typedef index_ upper_bound_;
	typedef typename decrement<typename Base::size>::type size;
	typedef Base base;
	typedef v_mask type;

	static type_wrapper<void_> item_(index_);
	using Base::item_;
};

template <typename Base>
struct v_mask<Base, true> : Base {
	typedef typename Base::lower_bound_ index_;
	typedef typename increment<index_>::type lower_bound_;
	typedef typename decrement<typename Base::size>::type size;
	typedef Base base;
	typedef v_mask type;

	static type_wrapper<void_> item_(index_);
	using Base::item_;
};

template <typename Vector, long n_>
struct v_at_impl {
	typedef long_<(Vector::lower_bound_::value + n_)> index_;
	typedef decltype(Vector::item_(index_())) type;
};

template <typename Vector, long n_>
struct v_at : wrapped_type<typename v_at_impl<Vector, n_>::type>
{};

template <typename Vector, long n_>
struct vector_iterator {
	typedef vector_iterator_tag tag;
	typedef random_access_iterator_tag category;
	typedef typename v_at<Vector, n_>::type type;

	typedef Vector vector_;
	typedef long_<n_> pos;
};

}

template <typename Vector, long n_>
struct next <detail::vector_iterator<Vector, n_>> {
	typedef detail::vector_iterator<Vector, (n_ + 1)> type;
};

template <typename Vector, long n_>
struct prior<detail::vector_iterator<Vector, n_>> {
	typedef detail::vector_iterator<Vector, (n_ - 1)> type;
};

template <typename Vector, long n_, typename Distance>
struct advance<detail::vector_iterator<Vector, n_>, Distance> {
	typedef detail::vector_iterator<Vector, (n_ + Distance::value)> type;
};

template <typename Vector, long n_, long m_>
struct distance<
	detail::vector_iterator<Vector, n_>,
	detail::vector_iterator<Vector, m_>
> : long_<(m_ - n_)> {};

template <typename...>
struct vector;

template <>
struct vector<> {
	typedef detail::vector_tag tag;
	typedef vector type;
	typedef long_<32768> lower_bound_;
	typedef lower_bound_ upper_bound_;
	typedef long_<0> size;

	static detail::type_wrapper<void_> item_(...);
};

template <typename T0>
struct vector<T0> : detail::v_item<T0, vector<>, true> {
	typedef vector type;
};

template <typename T0, typename... Tn>
struct vector<T0, Tn...> : detail::v_item<T0, vector<Tn...>, true> {
	typedef vector type;
};

template <typename T, T... Cn>
struct vector_c;

template <typename T>
struct vector_c<T> : vector<> {
	typedef vector_c type;
	typedef T value_type;
};

template <typename T, T C0, T... Cn>
struct vector_c<T, C0, Cn...>
: detail::v_item<integral_constant<T, C0>, vector_c<T, Cn...>, true> {
	typedef vector_c type;
	typedef T value_type;
};

namespace detail {

template <>
struct at_impl<vector_tag> {
	template <typename Vector, typename N>
	struct apply : v_at<Vector, N::value>
	{};
};

template <>
struct back_impl<vector_tag> {
	template <typename Vector>
	struct apply : v_at<
		Vector, decrement<typename Vector::size>::type::value
	> {};
};

template <>
struct begin_impl<vector_tag> {
	template <typename Vector>
	struct apply {
		typedef vector_iterator<Vector, 0> type;
	};
};

template <>
struct clear_impl<vector_tag> {
	template <typename Vector>
	struct apply {
		typedef vector<> type;
	};
};

template <>
struct empty_impl<vector_tag> {
	template <typename Vector>
	struct apply : std::is_same<
		typename Vector::lower_bound_, typename Vector::upper_bound_
	> {};
};

template <>
struct end_impl<vector_tag> {
	template <typename Vector>
	struct apply {
		typedef vector_iterator<Vector, Vector::size::value> type;
	};
};

template <>
struct front_impl<vector_tag> {
	template <typename Vector>
	struct apply : v_at<Vector, 0>
	{};
};

template <>
struct O1_size_impl<vector_tag> {
	template <typename Vector>
	struct apply : Vector::size {};
};

template <>
struct pop_back_impl<vector_tag> {
	template <typename Vector>
	struct apply {
		typedef v_mask<Vector, false> type;
	};
};

template <>
struct pop_front_impl<vector_tag> {
	template <typename Vector>
	struct apply {
		typedef v_mask<Vector, true> type;
	};
};

template <>
struct push_back_impl<vector_tag> {
	template <typename Vector, typename T>
	struct apply {
		typedef v_item<T, Vector, false> type;
	};
};

template <>
struct push_front_impl<vector_tag> {
	template <typename Vector, typename T>
	struct apply {
		typedef v_item<T, Vector, true> type;
	};
};

template <>
struct size_impl<vector_tag>
{
	template <typename Vector>
	struct apply : Vector::size {};
};

}
}}}

#endif
