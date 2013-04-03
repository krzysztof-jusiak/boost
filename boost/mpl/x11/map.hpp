/*=============================================================================
    Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>

    Based on original implementation:
        Copyright (c) 2000-2004 Aleksey Gurtovoy
        Copyright (c) 2003-2004 David Abrahams

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_MAP_APR_03_2013_1950)
#define MPL_X11_MAP_APR_03_2013_1950

#include <boost/mpl/x11/pair.hpp>
#include <boost/mpl/x11/logical.hpp>
#include <boost/mpl/x11/arithmetic.hpp>
#include <boost/mpl/x11/detail/type_wrapper.hpp>

#include <boost/mpl/x11/sequence_tag.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/iterator_tags.hpp>
#include <boost/mpl/x11/detail/clear.hpp>
#include <boost/mpl/x11/detail/order.hpp>
#include <boost/mpl/x11/deref.hpp>
#include <boost/mpl/x11/next_prior.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct map_tag;

template <typename Map, long order>
struct item_by_order_impl {
	decltype(Map::item_by_order_(
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

	static type_wrapper<T> value_by_key_(m_item const &, type_wrapper<Key>);
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

	static type_wrapper<void_> item_by_order_(m_mask const &, key_order_ *);
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

	decltype(Map::value_by_key_(
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
	typedef map<> type;
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

	static std::false_type order_by_key_(
		map<> const &, void const volatile *
	);
};


template <typename P0>
struct map<P0>
: detail::m_item<typename P0::first, typename P0::second, map<>> {
	typedef map<P0> type;
};

template <typename P0, typename P1>
struct map<P0, P1> : detail::m_item<
	typename P0::first, typename P0::second, map<P1>
> {
	typedef map<P0, P1> type;
};

template <typename P0, typename P1, typename... Pn>
struct map<P0, P1, Pn...> : detail::m_item<
	typename P0::first, typename P0::second, map<P1, Pn...>
> {
	typedef map<P0, P1, Pn...> type;
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
struct clear_impl<map_tag> {
	template <typename Map> struct apply {
		typedef map<> type;
	};
};

template <>
struct empty_impl<map_tag> {
	template <typename Map>
	struct apply : not_<typename Map::size> {};
};

template <>
struct size_impl<map_tag> {
	template <typename Map>
	struct apply : Map::size {};
};

}}}}

#endif
