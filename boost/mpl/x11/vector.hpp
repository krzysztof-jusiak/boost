/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_VECTOR_APR_10_2013_2330)
#define MPL_X11_VECTOR_APR_10_2013_2330

#include <boost/mpl/x11/detail/type_wrapper.hpp>
#include <boost/mpl/x11/next_prior.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct vector_tag;

struct v_iter_tag;

template <typename T, typename Base, int at_front = 0>
struct v_item : Base {
	typedef typename Base::upper_bound_ index_;
	typedef typename next<index_>::type upper_bound_;
	typedef typename next<typename Base::size>::type size;
	typedef Base base;
	typedef v_item type;

	static type_wrapper<T> item_(index_);
	using Base::item_;
};

template <typename T, typename Base>
struct v_item<T, Base, 1> : Base {
	typedef typename prior<typename Base::lower_bound_>::type index_;
	typedef index_ lower_bound_;
	typedef typename next<typename Base::size>::type size;
	typedef Base base;
	typedef v_item type;

	static type_wrapper<T> item_(index_);
	using Base::item_;
};

template <typename Base, int at_front>
struct v_mask : Base {
	typedef typename prior<typename Base::upper_bound_>::type index_;
	typedef index_ upper_bound_;
	typedef typename prior<typename Base::size>::type size;
	typedef Base base;
	typedef v_mask type;

	static type_wrapper<void_> item_(index_);
	using Base::item_;
};

template <typename Base>
struct v_mask<Base, 1> : Base {
	typedef typename Base::lower_bound_ index_;
	typedef typename next<index_>::type lower_bound_;
	typedef typename prior<typename Base::size>::type size;
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
struct v_iter {
	typedef v_iter_tag tag;
	typedef random_access_iterator_tag category;
	typedef typename v_at<Vector, n_>::type type;

	typedef Vector vector_;
	typedef long_<n_> pos;
};

}

template <typename...>
struct vector;

template <>
struct vector<> {
typedef aux::vector_tag tag;
	typedef vector type;
	typedef long_<32768> lower_bound_;
	typedef lower_bound_ upper_bound_;
	typedef long_<0> size;

	static detail::type_wrapper<void_> item_(...);
};

template <typename T0>
struct vector<T0> : detail::v_item<T0, vector<>> {
	typedef vector type;
};

template <typename T0, typename... Tn>
struct vector<T0, Tn...> : detail::v_item<T0, vector<Tn...>> {
	typedef vector type;
};

}}}

#endif
