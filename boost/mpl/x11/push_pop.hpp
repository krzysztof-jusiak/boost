/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_PUSH_POP_APR_03_2013_1345)
#define MPL_X11_PUSH_POP_APR_03_2013_1345

#include <boost/mpl/x11/detail/push_pop.hpp>
#include <boost/mpl/x11/sequence_tag.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename Sequence, typename T>
struct push_back : detail::push_back_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence, T>
{};

template <typename Sequence, typename T>
struct push_front : detail::push_front_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence, T>
{};

template <typename Sequence>
struct has_push_back : detail::has_push_back_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence>
{};

template <typename Sequence>
struct has_push_front : detail::has_push_front_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence>
{};

template <typename Sequence>
struct pop_back : detail::pop_back_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence>
{};


template <typename Sequence>
struct pop_front : detail::pop_front_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence>
{};

}}}

#endif
