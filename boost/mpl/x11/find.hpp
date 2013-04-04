/*=============================================================================
    Copyright (c) 2000-2002 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_FIND_APR_04_2013_1545)
#define MPL_X11_FIND_APR_04_2013_1545

#include <boost/mpl/x11/detail/iter_apply.hpp>
#include <boost/mpl/x11/arg.hpp>
#include <boost/mpl/x11/same_as.hpp>
#include <boost/mpl/x11/identity.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Predicate>
struct find_if_pred {
	template <typename Iterator>
	struct apply {
		typedef not_<iter_apply<Predicate, Iterator>> type;
	};
};

}

template <typename Sequence, typename Predicate>
struct find_if {
	typedef typename iter_fold_if<
		Sequence, void, arg<0>,
		protect<detail::find_if_pred<Predicate>>
	>::type result_;

	typedef typename second<result_>::type type;
};

template <typename Sequence, typename T>
struct find : find_if <Sequence, same_as<T>> {};

}}}

#endif
