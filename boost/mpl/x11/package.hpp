/*=============================================================================
    Copyright (c) 2007      Larry Evans
        Permission to copy, use, modify, sell and distribute this software
        is granted provided this copyright notice appears in all copies.
        This software is provided "as is" without express or implied
        warranty, and with no claim as to its suitability for any purpose.

    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_PACKAGE_APR_14_2013_2300)
#define MPL_X11_PACKAGE_APR_14_2013_2300

#include <boost/mpl/x11/iterator_tags.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/deref.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct package_tag;

}

template <typename...>
struct package {
	typedef detail::package_tag tag;
	typedef package type;
};

template <typename T, T... C>
struct package_c : package<integral_constant<T, C>...> {
	typedef T value_type;
	typedef package_c type;
};

namespace detail {

template <typename... Tn>
struct p_iter {
	typedef forward_iterator_tag category;
};

template <>
struct at_impl<package_tag> {
	template <typename Package, long n_>
	struct apply_impl;

	template <typename T0, typename... Tn>
	struct apply_impl<package<T0, Tn...>, 0> {
		typedef T0 type;
	};

	template <typename T0, typename... Tn, long n_>
	struct apply_impl<package<T0, Tn...>, n_>
	: apply_impl<package<Tn...>, n_ - 1> {};

	template <typename Package, long n_>
	struct apply : apply_impl<typename Package::type, n_> {};
};

template <>
struct begin_impl<package_tag> {
	template <typename...>
	struct apply_impl;

	template <typename... Tn>
	struct apply_impl<package<Tn...>> {
		typedef p_iter<Tn...> type;
	};

	template <typename Package>
	struct apply : apply_impl<typename Package::type> {};
};

template <>
struct clear_impl<package_tag> {
	template <typename...>
	struct apply_impl;

	template <typename... Tn>
	struct apply_impl<package<Tn...>> {
		typedef package<> type;
	};

	template <typename Package>
	struct apply : apply_impl<typename Package::type> {};
};

template <>
struct end_impl<package_tag> {
	template <typename...>
	struct apply_impl;

	template <typename... Tn>
	struct apply_impl<package<Tn...>> {
		typedef p_iter<> type;
	};

	template <typename Package>
	struct apply : apply_impl<typename Package::type> {};
};

template <>
struct front_impl<package_tag> {
	template <typename...>
	struct apply_impl;

	template <typename T0, typename... Tn>
	struct apply_impl<package<T0, Tn...>> {
		typedef T0 type;
	};

	template <typename Package>
	struct apply : apply_impl<typename Package::type> {};
};

template <>
struct pop_front_impl<package_tag> {
	template <typename...>
	struct apply_impl;

	template <
		typename... Tn, typename T0,
		template <typename...> class Package
	> struct apply_impl<Package<T0, Tn...>> {
		typedef Package<Tn...> type;
	};

	template <class Package>
	struct apply : apply_impl<typename Package::type> {};
};

template <>
struct push_back_impl<package_tag> {
	template <typename...>
	struct apply_impl;

	template <
		typename... Tn, typename T0,
		template <typename...> class Package
	> struct apply_impl<Package<Tn...>, T0> {
		typedef Package<Tn..., T0> type;
	};

	template <typename Package, typename T>
	struct apply : apply_impl<typename Package::type, T> {};
};

template <>
struct push_front_impl<package_tag> {
	template <typename Package, typename T>
	struct apply_impl;

	template <
		typename... Tn, typename T0,
		template <typename...> class Package
	> struct apply_impl<Package<Tn...>, T0> {
		typedef Package<T0, Tn...> type;
	};

	template <typename Package, typename T>
	struct apply : apply_impl<typename Package::type, T> {};
};

template <>
struct size_impl<package_tag> {
	template <typename...>
	struct apply_impl;

	template <typename... Tn>
	struct apply_impl<package<Tn...>>
	: integral_constant<long, sizeof...(Tn)> {};

	template <typename Package>
	struct apply : apply_impl<typename Package::type> {};
};

}

template <typename T0, typename... Tn>
struct deref<detail::p_iter<T0, Tn...>> {
	typedef T0 type;
};

template <typename T0, typename... Tn>
struct next<detail::p_iter<T0, Tn...>> {
	typedef detail::p_iter<Tn...> type;
};

}}}

#endif
