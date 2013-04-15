/*=============================================================================
    Copyright (c) 2003-2004 Aleksey Gurtovoy
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_SET_APR_15_2013_1130)
#define MPL_X11_SET_APR_15_2013_1130

#include <boost/mpl/x11/iterator_tags.hpp>
#include <boost/mpl/x11/logical.hpp>

#include <boost/mpl/x11/void.hpp>
#include <boost/mpl/x11/if.hpp>
#include <boost/mpl/x11/arithmetic.hpp>
#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/has_key.hpp>
#include <boost/mpl/x11/base.hpp>

#include <boost/mpl/x11/detail/begin_end.hpp>
#include <boost/mpl/x11/detail/size.hpp>
#include <boost/mpl/x11/detail/type_wrapper.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct set_tag;

template <typename T, typename Base>
struct s_item : Base {
	typedef s_item<T, Base> item_;
	typedef void_ last_masked_;
	typedef T item_type_;
	typedef Base base;

	typedef typename increment<typename Base::size>::type size;
	typedef typename increment<typename Base::order>::type order;

	typedef char (&order_tag_)[order::value];

	static order_tag_ order_by_key_(s_item const&, type_wrapper<T>*);
	using Base::order_by_key_;

	static true_type is_masked_(s_item const&, type_wrapper<T>*);
	using Base::is_masked_;
};

template <typename T, typename Base>
struct s_mask : Base {
	typedef s_mask<T, Base> item_;
	typedef T last_masked_;
	typedef void_ item_type_;
	typedef Base base;
	typedef typename decrement<typename Base::size>::type size;

	static false_type is_masked_(s_mask const&, type_wrapper<T>*);
	using Base::is_masked_;
};

template <typename T, typename Base>
struct s_unmask : Base {
	typedef s_unmask<T, Base> item_;
	typedef void_ last_masked_;
	typedef T item_type_;
	typedef Base base;
	typedef typename increment<typename Base::size>::type size;

	static true_type is_masked_(s_unmask const&, type_wrapper<T>*);
	using Base::is_masked_;
};

template <typename Set, typename Tail>
struct s_iter;

template <typename Set, typename Tail>
struct s_iter_get : eval_if<
	x11::has_key<Set, typename Tail::item_type_>,
	identity<s_iter<Set, Tail>>,
	next<s_iter<Set, Tail>>
> {};

template <typename Set, typename Tail>
struct s_iter_impl {
	typedef Tail tail_;
	typedef forward_iterator_tag category;
	typedef typename Tail::item_type_ type;
};

}

template <typename...>
struct set;

template <>
struct set<> {
	typedef set<> item_;
	typedef item_ type;
	typedef detail::set_tag tag;
	typedef void_ last_masked_;
	typedef void_ item_type_;
	typedef long_<0> size;
	typedef long_<1> order;

	typedef char (&order_tag_)[1];
 
	static order_tag_ order_by_key_(set<> const &, void const volatile *);
	static false_type is_masked_(set<> const &, void const volatile *);
};

template <typename T0>
struct set<T0> : detail::s_item<T0, typename set<>::item_> {
	typedef set type;
};

template <typename T0, typename... Tn>
struct set<T0, Tn...> : detail::s_item<T0, typename set<Tn...>::item_> {
	typedef set type;
};

template <typename T, T... Cn>
struct set_c;

template <typename T>
struct set_c<T> : set<> {
	typedef set_c type;
	typedef T value_type;
};

template <typename T, T C0>
struct set_c<T, C0>
: detail::s_item<integral_constant<T, C0>, typename set_c<T>::item_> {
	typedef set_c type;
	typedef T value_type;
};

template <typename T, T C0, T... Cn>
struct set_c<T, C0, Cn...>
: detail::s_item<integral_constant<T, C0>, typename set_c<T, Cn...>::item_> {
	typedef set_c type;
	typedef T value_type;
};

template <typename Set, typename Tail>
struct next<detail::s_iter<Set, Tail>>
: detail::s_iter_get<Set, typename Tail::base> {};

template <typename Set>
struct next<detail::s_iter<Set, set<>>> {
    typedef detail::s_iter<Set, set<>> type;
};

namespace detail {

template <typename Set, typename Tail>
struct s_iter : s_iter_impl<Set, Tail> {};

template <typename Set>
struct s_iter<Set, set<>> {
	typedef forward_iterator_tag category;
};

template <>
struct has_key_impl<set_tag> {
	template <typename Set, typename T>
	struct apply : decltype(Set::is_masked_(
		ptr_to_ref(static_cast<Set *>(0)),
		static_cast<type_wrapper<T> *>(0)
	)) {};
};

template <>
struct at_impl<set_tag> {
	template <typename Set, typename T>
	struct apply {
		typedef typename if_<
			has_key_impl<set_tag>::apply<Set,T>, T, void_
		>::type type;
	};
};

template <>
struct begin_impl<set_tag> {
	template <typename Set>
	struct apply : s_iter_get<Set, typename Set::item_> {};
};

template <>
struct clear_impl<set_tag> {
	template <typename Set>
	struct apply {
		typedef set<> type;
	};
};

template <>
struct empty_impl<set_tag> {
	template <typename Set>
	struct apply : not_<typename Set::size> {};
};

template <>
struct end_impl<set_tag> {
	template <typename Set>
	struct apply {
		typedef s_iter<Set, set<>> type;
	};
};

template <>
struct erase_key_impl<set_tag> {
	template <typename Set, typename T>
	struct apply : eval_if<
		has_key_impl<set_tag>::apply<Set,T>,
		eval_if<
			std::is_same<T, typename Set::item_type_>,
			base<Set>,
			identity<s_mask<T, typename Set::item_>>
		>, identity<Set>
	> {};
};

template <>
struct erase_impl<set_tag> {
	template <typename Set, typename Pos, typename unused_>
	struct apply
	: erase_key_impl<set_tag>::apply<Set, typename Pos::type> {};
};

template <>
struct insert_impl<set_tag>
{
	template <typename Set, typename T>
	struct apply_impl : eval_if<
		has_key_impl<set_tag>::apply<Set,T>,
		identity<Set>,
		eval_if<
			std::is_same<T, typename Set::last_masked_>,
			base<Set>,
			identity<s_item<T, typename Set::item_>>
		>
	> {};

	template <typename...>
	struct apply;

	template <typename Set, typename Pos>
	struct apply<Set, Pos> : apply_impl<Set, Pos> {};

	template <typename Set, typename Pos, typename T>
	struct apply<Set, Pos, T> : apply_impl<Set, T> {};
};

template <>
struct key_type_impl<set_tag> {
	template <typename Set, typename T>
	struct apply {
		typedef T type;
	};
};

template <>
struct size_impl<set_tag> {
	template <typename Set>
	struct apply : Set::size {};
};

template <>
struct value_type_impl<set_tag> {
	template <typename Set, typename T>
	struct apply {
		typedef T type;
	};
};

}

}}}

#endif
