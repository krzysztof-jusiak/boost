/*=============================================================================
    Copyright (c) 2003-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_MULTISET_APR_29_2013_1800)
#define MPL_X11_MULTISET_APR_29_2013_1800

#include <boost/mpl/x11/detail/type_wrapper.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct multiset_tag;

template <typename U, typename Base>
struct prior_key_count {
	typedef int_<
		sizeof(Base::key_count(static_cast<type_wrapper<U> *>(0)))
	> count_;

	typedef char (&type)[count_::value];
};

template <typename T, typename Base>
struct multiset_item {
	typedef multiset_tag tag;

	typedef int_<(
		sizeof(Base::key_count(static_cast<type_wrapper<T> *>(0))) + 1
	)> count_;

	static char (&key_count(type_wrapper<T> *))[count_::value];

	template <typename U>
	static typename prior_key_count<U, Base>::type key_count(
		type_wrapper<U> *
	);
};

template <>
struct insert_impl<multiset_tag> {
	template <typename Set, typename Key, typename unused_>
	struct apply {
		typedef multiset_item<Key, Set> type;
	};
};

template <>
struct count_impl<multiset_tag> {
	template <typename Set, typename Key>
	struct apply {
		enum {
			pos_ = sizeof(Set::key_count(
				static_cast<type_wrapper<Key> *>(0)
			)) - 1
		};
		typedef int_<pos_> type;
		static const int value = pos_;
	};
};

}

template <int dummy_ = 0>
struct multiset {
	typedef detail::multiset_tag tag;

	typedef int_<1> count_;
	static char (& key_count(...) )[count_::value];
	static char (& ref_key_count(...) )[count_::value];
};

}}}

#endif
