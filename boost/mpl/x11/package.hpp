/*==============================================================================
    Copyright (c) 2007      Larry Evans
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_PACKAGE_APR_30_2013_1745)
#define MPL_X11_PACKAGE_APR_30_2013_1745

#include <boost/mpl/x11/iterator_tags.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/deref.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct package_tag;

}

template <typename... Tn>
struct package {
	typedef detail::package_tag tag;

	typedef package<Tn...> type;
	typedef type pkg_type;
};

template <typename T, T... Cn>
struct package_c : package<integral_constant<T, Cn>...> {
	typedef package_c type;
	typedef T value_type;
};

namespace detail {

template <typename... Tn>
struct iterator_fwd {
	typedef forward_iterator_tag category;
};

template <>
struct at_impl<package_tag> {
	template <typename Package, long N>
	struct apply_impl;

	template <typename T0, typename... Tn>
	struct apply_impl<package<T0, Tn...>, 0> {
		typedef T0 type;
	};

	template <typename T0, typename... Tn, long N>
	struct apply_impl<package<T0, Tn...>, N>
	: apply_impl<package<Tn...>, N - 1> {};

	template <typename Package, typename N>
	struct apply : apply_impl<typename Package::pkg_type, N::value> {};
};

template <>
struct begin_impl<package_tag> {
	template <typename Package>
	struct apply_impl;

	template<typename... Tn>
	struct apply_impl<package<Tn...>> {  
		typedef iterator_fwd<Tn...> type;
	};

	template <typename Package>
	struct apply : apply_impl<typename Package::pkg_type> {};
};

template <>
struct clear_impl<package_tag> {
	template <typename Package>
	struct apply_impl;

	template <typename... Tn>
	struct apply_impl<package<Tn...>> {
		typedef package<> type;
	};

	template <typename Package>
	struct apply : apply_impl<Package> {};
};
    
template <>
struct end_impl<package_tag> {
	template <typename Package>
	struct apply_impl;

	template <typename... Tn>
	struct apply_impl<package<Tn...>> {  
		typedef iterator_fwd<> type;
        };

	template <typename Package>
	struct apply : apply_impl<typename Package::pkg_type> {};
};

template <>
struct front_impl<package_tag> {
	template <typename Package>
	struct apply_impl;

	template <typename T0, typename... Tn>
	struct apply_impl<package<T0, Tn...>> {  
		typedef T0 type;
	};

	template <typename Package>
	struct apply : apply_impl<typename Package::pkg_type> {};
};

template <>
struct pop_front_impl<package_tag> {
	template <typename Package>
	struct apply_impl;

	template <
		typename... Tn, typename T0,
		template <typename...> class Package
	> struct apply_impl<Package<T0, Tn...>> {
		typedef Package<Tn...> type;
	};

	template <typename Package>
	struct apply : apply_impl<Package> {};
};

template <>
struct push_back_impl<package_tag> {
	template <typename Package, typename Tn>
	struct apply_impl;

	template <
		typename... Tn, typename T0,
		template <typename...> class Package
	> struct apply_impl<Package<Tn...>, T0> {  
		typedef Package<Tn..., T0> type;
	};

	template <typename Package, typename Tn>
	struct apply : apply_impl<Package, Tn> {};
};

template <>
struct push_front_impl<package_tag> {
	template <typename Package, typename T0>
	struct apply_impl;

	template <
		typename... Tn, typename T0,
		template <typename...> class Package
	> struct apply_impl<Package<Tn...>, T0> {  
		typedef Package<T0, Tn...> type;
	};

	template <typename Package, typename T0>
	struct apply : apply_impl<Package, T0> {};
};

template <>
struct size_impl<package_tag> {
	template <typename Package>
	struct apply_impl;

	template <typename... Args>
	struct apply_impl<package<Args...>> : long_<sizeof...(Args)> {};

	template <typename Package>
	struct apply : apply_impl<typename Package::pkg_type> {};
};

}

template <typename T0, typename... Tn>
struct deref<detail::iterator_fwd<T0, Tn...>> {
	typedef T0 type;
};

template <typename T0, typename... Tn>
struct next<detail::iterator_fwd<T0, Tn...>> {
	typedef detail::iterator_fwd<Tn...> type;
};

}}}

#endif
