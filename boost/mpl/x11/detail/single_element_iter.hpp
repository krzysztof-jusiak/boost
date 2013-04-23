/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_SINGLE_ELEMENT_ITER_APR_23_2013_2300)
#define MPL_X11_SINGLE_ELEMENT_ITER_APR_23_2013_2300

#include <boost/mpl/x11/iterator_tags.hpp>
#include <boost/mpl/x11/advance.hpp>
#include <boost/mpl/x11/distance.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template< typename T, long is_last_>
struct sel_iter;

template <typename T>
struct sel_iter<T, 0> {
	typedef random_access_iterator_tag category;
	typedef sel_iter<T, 1> next;
	typedef T type;
};

template<typename T>
struct sel_iter<T, 1> {
	typedef random_access_iterator_tag category;
	typedef sel_iter<T, 0> prior;
};

}

template <typename T, long is_last_, typename Distance>
struct advance<detail::sel_iter<T, is_last_>, Distance> {
	typedef detail::sel_iter<T, ( is_last_ + Distance::value)> type;
};

template <typename T, long l1, long l2>
struct distance<detail::sel_iter<T, l1>, detail::sel_iter<T, l2>>
: long_<( l2 - l1 )> {};

}}}

#endif
