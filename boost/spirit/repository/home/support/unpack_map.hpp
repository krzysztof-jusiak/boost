/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_SUPPORT_UNPACK_MAP_MAY_02_2013_2300)
#define SPIRIT_REPOSITORY_SUPPORT_UNPACK_MAP_MAY_02_2013_2300

#include <boost/mpl/x11/at.hpp>
#include <boost/mpl/x11/package.hpp>
#include <boost/mpl/x11/has_key.hpp>
#include <boost/mpl/x11/transform.hpp>

namespace boost { namespace spirit { namespace repository {
namespace detail {

template <typename F, typename Map, typename Tpack>
struct unpack_map_impl;

template <typename F, typename Map, typename... Tkey>
struct unpack_map_impl<F, Map, boost::mpl::x11::package<Tkey...>>
: boost::mpl::x11::apply<
	F, boost::mpl::x11::package<Tkey...>,
	typename boost::mpl::x11::at<Map, Tkey>::type...
> {};

}

template <typename...>
struct unpack_map;

/* Unordered version */
template <typename F>
struct unpack_map<F> {
	template <typename Map>
	struct apply : detail::unpack_map_impl<
		F, Map, typename boost::mpl::x11::transform1<
			Map, boost::mpl::x11::first<boost::mpl::x11::arg<0>>,
			boost::mpl::x11::back_inserter<
				boost::mpl::x11::package<>
			>
		>::type
        > {};
};

/* Ordered version, using OrdSeq as guide for unpacking */
template <typename F, typename OrdSeq>
struct unpack_map<F, OrdSeq> {
	template <typename Map>
	struct apply : detail::unpack_map_impl<
		F, Map, typename boost::mpl::x11::fold<
			OrdSeq, boost::mpl::x11::package<>,
			boost::mpl::x11::eval_if<
				boost::mpl::x11::has_key<
					Map, boost::mpl::x11::arg<1>
				>,
				boost::mpl::x11::push_back<
					boost::mpl::x11::arg<0>,
					boost::mpl::x11::arg<1>
				>,
				boost::mpl::x11::identity<
					boost::mpl::x11::arg<0>
				>
			>
		>::type
        > {};
};

}}}

#endif
