/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_ITERATOR_CATEGORY_APR_19_2013_1130)
#define MPL_X11_ITERATOR_CATEGORY_APR_19_2013_1130

#include <boost/mpl/x11/lambda_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename...>
struct iterator_category;

template <>
struct iterator_category<> {
	template <typename T0, typename... Tn>
	struct apply : iterator_category<T0> {};
};

template <typename Tag>
struct lambda<iterator_category<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef iterator_category<> result_;
	typedef iterator_category<> type;
};

template <typename Iterator>
struct iterator_category<Iterator> {
	typedef typename Iterator::category type;
};

}}}

#endif
