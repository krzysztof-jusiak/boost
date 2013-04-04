/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_SEQUENCE_FWD_APR_03_2013_1300)
#define MPL_X11_SEQUENCE_FWD_APR_03_2013_1300

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Tag> struct advance_impl;
template <typename Tag> struct at_impl;
template <typename Tag> struct back_impl;
template <typename Tag> struct begin_impl;
template <typename Tag> struct clear_impl;
template <typename Tag> struct contains_impl;
template <typename Tag> struct count_impl;
template <typename Tag> struct distance_impl;
template <typename Tag> struct erase_impl;
template <typename Tag> struct erase_key_impl;
template <typename Tag> struct empty_impl;
template <typename Tag> struct end_impl;
template <typename Tag> struct front_impl;
template <typename Tag> struct has_key_impl;
template <typename Tag> struct has_push_back_impl;
template <typename Tag> struct insert_impl;
template <typename Tag> struct insert_range_impl;
template <typename Tag> struct key_type_impl;
template <typename Tag> struct order_impl;
template <typename Tag> struct pop_back_impl;
template <typename Tag> struct pop_front_impl;
template <typename Tag> struct push_back_impl;
template <typename Tag> struct push_front_impl;
template <typename Tag> struct size_impl;
template <typename Tag> struct value_type_impl;

}

template <typename Iterator, typename N> struct advance;
template <typename Sequence, typename N> struct at;

template <typename Sequence> struct back;
template <typename Sequence> struct begin;
template <typename Sequence> struct clear;

template <typename First, typename Last> struct distance;

template <typename Sequence, typename T> struct contains;
template <typename Sequence, typename T> struct count;

template <typename Sequence> struct empty;
template <typename Sequence> struct end;

template <typename Sequence, typename First, typename Last> struct erase;

template <typename Sequence, typename Key> struct erase_key;

template <typename Sequence> struct front;

template <typename Sequence, typename Key> struct has_key;

template <typename...> struct insert;

template <typename Sequence, typename Position, typename Range>
struct insert_range;

template <typename Sequence, typename T> struct key_type;

template <typename Sequence, typename Key> struct order;

template <typename Sequence> struct pop_back;
template <typename Sequence> struct pop_front;

template <typename Sequence, typename T> struct push_back;
template <typename Sequence, typename T> struct push_front;

template <typename Sequence> struct size;

template <typename Sequence, typename T> struct value_type;

}}}

#endif
