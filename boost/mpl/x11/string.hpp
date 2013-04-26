/*==============================================================================
    Copyright (c) 2009      Eric Niebler
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_STRING_APR_26_2013_1445)
#define MPL_X11_STRING_APR_26_2013_1445

#include <boost/mpl/x11/vector.hpp>
#include <boost/mpl/x11/fold.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct string_tag;
struct string_iterator_tag;

template <typename T>
struct nibble_size_impl;

template <int C>
struct nibble_size_impl<integral_constant<int, C>>
: long_<(0 + long(
	(C < (-127 - 1)) ? 4 : ((C > 0xffffff) + (C > 0xffff) + (C > 0xff) + 1)
))> {};

template <typename String, long m_, long n_>
struct string_iterator {
	typedef typename v_at<typename String::base, m_>::type nibble_;
	typedef typename v_at<typename String::base, m_ - 1>::type prev_nibble_;
	static const bool eocn_ = (nibble_size_impl<nibble_>::value == n_ + 1);

	typedef string_iterator_tag tag;
	typedef bidirectional_iterator_tag category;
	typedef String string_;

	typedef string_iterator<
		string_,
		eocn_ ? m_ + 1 : 0,
		eocn_ ? 0 : n_ + 1
	> next;
	typedef string_iterator<
		string_,
		n_ ? m_ : m_ - 1,
		n_ ? n_ - 1 : (nibble_size_impl<prev_nibble_>::value - 1)
	> prior;

	typedef char_<char(0xff & (
		unsigned(nibble_::value)
		>> (8 * (
			nibble_size_impl<nibble_>::value - std::size_t(n_) - 1
		))
	))> type;
};

}

template <int... Cn>
struct string {
	typedef vector_c<int, Cn...> base;

	typedef char value_type;
	typedef string type;
	typedef detail::string_tag tag;
};

namespace detail {

template <>
struct begin_impl<string_tag> {
	template <typename String>
	struct apply {
		typedef string_iterator<String, 0, 0> type;
	};
};

template <>
struct end_impl<string_tag> {
	template <typename String>
	struct apply {
		typedef string_iterator<
			String, O1_size<typename String::base>::value, 0
		> type;
	};
};

template <>
struct size_impl<string_tag> {
	struct apply_impl {
		template <typename T0, typename T1>
		struct apply {
			typedef plus<T0, nibble_size_impl<T1>> type;
		};
	};

	template <typename Sequence>
	struct apply : fold<
		typename Sequence::base, long_<0>,
		bind<apply_impl, arg<0>, arg<1>>
	> {};
};

}


}}}

#endif
