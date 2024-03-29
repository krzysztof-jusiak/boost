/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_MAP_APR_03_2013_1950)
#define MPL_X11_MAP_APR_03_2013_1950

#include <boost/mpl/x11/if.hpp>
#include <boost/mpl/x11/base.hpp>
#include <boost/mpl/x11/pair.hpp>
#include <boost/mpl/x11/void.hpp>
#include <boost/mpl/x11/logical.hpp>
#include <boost/mpl/x11/arithmetic.hpp>
#include <boost/mpl/x11/iterator_tags.hpp>
#include <boost/mpl/x11/next_prior.hpp>

#include <boost/mpl/x11/detail/at.hpp>
#include <boost/mpl/x11/detail/clear.hpp>
#include <boost/mpl/x11/detail/contains.hpp>
#include <boost/mpl/x11/detail/erase.hpp>
#include <boost/mpl/x11/detail/has_key.hpp>
#include <boost/mpl/x11/detail/order.hpp>
#include <boost/mpl/x11/detail/type_wrapper.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct map_tag;

template <typename Map, long order>
struct item_by_order_impl {
	typedef decltype(Map::item_by_order_(
		ptr_to_ref(static_cast<Map *>(nullptr)),
		static_cast<long_<order> *>(nullptr)
	)) type;
};

template <typename Map, long order>
struct item_by_order
: wrapped_type<typename item_by_order_impl<Map, order>::type> {};

template <typename Key, typename T, typename Base>
struct m_item : Base {
	typedef Key key_;
	typedef pair<Key, T> item;
	typedef Base base;

	typedef typename increment<typename Base::size>::type size;
	typedef typename increment<typename Base::order>::type order;

	typedef char (&order_tag_)[order::value];

	static type_wrapper<T> value_by_key_(
		m_item const &, type_wrapper<Key> *
	);
	using Base::value_by_key_;

	static type_wrapper<item> item_by_order_(m_item const &, order *);
	using Base::item_by_order_;
	
	static order_tag_ order_by_key_(m_item const &, type_wrapper<Key> *);
	using Base::order_by_key_;
};

template <typename Key, typename Base>
struct m_mask : Base {
	typedef void_ key_;
	typedef Base base;

	typedef typename decrement<typename Base::size>::type size;
	typedef typename x_order_impl<Base, Key>::type key_order_;

	static type_wrapper<void_> value_by_key_(
		m_mask const &, type_wrapper<Key> *
	);
	using Base::value_by_key_;

	static type_wrapper<void_> item_by_order_(
		m_mask const &, key_order_ *
	);
	using Base::item_by_order_;
};

template <typename Map, long order, long max_order>
struct next_order : if_<
	is_void_<typename item_by_order<Map, order>::type>,
	next_order<Map, (order + 1), max_order>,
	long_<order>
>::type {};

template <typename Map, long max_order>
struct next_order<Map, max_order, max_order> : long_<max_order> {};

template <typename Map, long order, long max_order>
struct m_iter {
	typedef forward_iterator_tag category;
	typedef typename item_by_order<Map, order>::type type;
};

template <typename Map, long max_order>
struct m_iter<Map, max_order, max_order> {
	typedef forward_iterator_tag category;
};

template <typename Map, typename Key>
struct m_at {
	typedef type_wrapper<Key> key_;

	typedef decltype(Map::value_by_key_(
		ptr_to_ref(static_cast<Map *>(nullptr)),
		static_cast<key_ *>(nullptr)
	)) type;
};

}

template <typename Map, long order, long max_order>
struct next<detail::m_iter<Map, order, max_order>> {
	typedef detail::m_iter<
		Map,
		detail::next_order<Map, order + 1, max_order>::value,
		max_order
	> type;
};

template <typename Map, long max_order>
struct next<detail::m_iter<Map, max_order, max_order>> {};

template <typename...>
struct map;

template <>
struct map<> {
	typedef map type;
	typedef detail::map_tag tag;
	typedef void_ key_;
	typedef long_<1> order;
	typedef long_<0> size;

	static detail::type_wrapper<void_> value_by_key_(
		map<> const &, void const volatile *
	);

	static detail::type_wrapper<void_> item_by_order_(
		map<> const &, long_<1> *
	);

	static false_type order_by_key_(
		map<> const &, void const volatile *
	);
};


template <typename P0>
struct map<P0>
: detail::m_item<typename P0::first, typename P0::second, map<>> {
	typedef map type;
};

template <typename P0, typename... Pn>
struct map<P0, Pn...> : detail::m_item<
	typename P0::first, typename P0::second, map<Pn...>
> {
	typedef map type;
};

namespace detail {

template <>
struct at_impl<map_tag> {
	template <typename Map, typename Key>
	struct apply : wrapped_type<
		typename m_at<Map, Key>::type
	> {};
};

template <>
struct begin_impl<map_tag> {
	template <typename Map>
	struct apply {
		typedef typename increment<
			typename Map::order
		>::type max_order_;

		typedef m_iter<
			Map,
			next_order<Map, 1, max_order_::value>::value,
			max_order_::value
		> type;
	};
};

template <>
struct clear_impl<map_tag> {
	template <typename Map> struct apply {
		typedef map<> type;
	};
};

template <>
struct contains_impl<map_tag> {
	template <typename Map, typename Pair>
	struct apply : std::is_same<
		typename at_impl<map_tag>::apply<
			Map, typename Pair::first
		>::type,
		typename Pair::second
	> {};
};


template <>
struct empty_impl<map_tag> {
	template <typename Map>
	struct apply : not_<typename Map::size> {};
};

template <>
struct end_impl<map_tag> {
	template <typename Map>
	struct apply {
		typedef typename increment<
			typename Map::order
		>::type max_order_;

		typedef m_iter <
			Map, max_order_::value, max_order_::value
		> type;
	};
};

template <>
struct has_key_impl<map_tag> {
	template <typename Map, typename Key>
	struct apply : is_not_void_<
		typename at_impl<map_tag>::apply<Map, Key>::type
	> {};
};

template <>
struct erase_key_impl<map_tag> {
	template<typename Map, typename Key>
	struct apply : eval_if<
		has_key_impl<map_tag>::apply<Map, Key>,
		eval_if<
			std::is_same<Key, typename Map::key_>,
			base<Map>, identity<m_mask<Key, Map>>
		>,
		identity<Map>
	> {};
};

template <>
struct erase_impl<map_tag> {
	template<typename Map, typename Pos, typename unused_>
	struct apply
	: erase_key_impl<map_tag>::apply<Map, typename Pos::type::first> {};
};

template <>
struct insert_impl<map_tag> {
	template <typename Map, typename Pair>
	struct apply_impl : if_<
		contains_impl<map_tag>::apply<Map, Pair>,
		Map,
		m_item<typename Pair::first, typename Pair::second, Map>
	> {};

	template <typename...>
	struct apply;

	template <typename Map, typename Pos>
	struct apply<Map, Pos> : apply_impl<Map, Pos> {};

	template <typename Map, typename Pos, typename T>
	struct apply<Map, Pos, T> : apply_impl<Map, T> {};
};

template <>
struct key_type_impl<map_tag> {
	template <typename Map, typename T>
	struct apply : first<T> {};
};

template <>
struct size_impl<map_tag> {
	template <typename Map>
	struct apply : Map::size {};
};

template <>
struct value_type_impl<map_tag> {
	template <typename Map, typename T>
	struct apply : second<T> {};
};

}}}}

#endif
