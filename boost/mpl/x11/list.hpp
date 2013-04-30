/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_LIST_APR_02_2013_1710)
#define MPL_X11_LIST_APR_02_2013_1710

#include <boost/mpl/x11/logical.hpp>
#include <boost/mpl/x11/arithmetic.hpp>
#include <boost/mpl/x11/detail/type_wrapper.hpp>

#include <boost/mpl/x11/sequence_tag.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/iterator_tags.hpp>
#include <boost/mpl/x11/deref.hpp>
#include <boost/mpl/x11/next_prior.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct list_tag;
struct list_iterator_tag;

template <typename Size, typename T, typename Next>
struct l_item {
	typedef list_tag tag;
	typedef l_item type;
	typedef Size size;
	typedef T item;
	typedef Next next;
};

struct l_end {
	typedef list_tag tag;
	typedef l_end type;
	typedef long_<0> size;
};

template <typename Node>
struct list_iterator {
	typedef list_iterator_tag tag;
	typedef forward_iterator_tag category;
};

template <>
struct list_iterator<l_end> {
	typedef list_iterator_tag tag;
	typedef forward_iterator_tag category;
};

template <>
struct begin_impl<list_tag> {
	template <typename List>
	struct apply {
		typedef list_iterator<typename List::type> type;
	};
};

template <>
struct clear_impl<list_tag> {
	template <typename List> struct apply {
		typedef l_end type;
	};
};

template <>
struct empty_impl<list_tag> {
	template <typename List>
	struct apply : not_<typename List::size> {};
};

template <>
struct end_impl<list_tag> {
	template <typename List>
	struct apply {
		typedef list_iterator<l_end> type;
        };
};

template <>
struct front_impl<list_tag> {
	template <typename List>
	struct apply {
		typedef typename List::item type;
	};
};

template <>
struct has_push_back_impl<list_tag> {
	template <typename Seq>
	struct apply : false_type {};
};

template <>
struct O1_size_impl<list_tag> {
	template <typename List>
	struct apply : List::size {};
};

template <>
struct pop_front_impl<list_tag> {
	template <typename List>
	struct apply {
		typedef typename next<List>::type type;
	};
};

template <>
struct push_front_impl<list_tag> {
	template<typename List, typename T>
	struct apply {
		typedef l_item<
			typename increment<typename List::size>::type,
			T, typename List::type
		> type;
	};
};

template <>
struct size_impl<list_tag> {
	template <typename List>
	struct apply : List::size {};
};

}

template <typename Node>
struct deref<detail::list_iterator<Node>> {
	typedef typename Node::item type;
};

template <typename Node>
struct next<detail::list_iterator<Node>> {
	typedef detail::list_iterator<typename Node::next> type;
};

template <typename T, typename Tag>
struct lambda<detail::list_iterator<T>, Tag, int_<1>> {
	typedef false_type is_le;
	typedef detail::list_iterator<T> result_;
	typedef result_ type;
};

template <typename...>
struct list;

template <>
struct list<> : detail::l_end {
	typedef detail::l_end type;
};

template <typename T0>
struct list<T0> : detail::l_item<long_<1>, T0, detail::l_end> {
	typedef list type;
};

template <typename T0, typename... Tn>
struct list<T0, Tn...> : detail::l_item<
	increment<typename list<Tn...>::size>,
	T0, list<Tn...>
> {
	typedef list type;
};

template <typename T, T... Cn>
struct list_c : list<integral_constant<T, Cn>...> {
	typedef list_c type;
	typedef T value_type;
};

}}}

#endif
