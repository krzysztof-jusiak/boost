/*=============================================================================
    Copyright (c) 2004      Aleksey Gurtovoy
    Copyright (c) 2004      Alexander Nasonov
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_EMPTY_SEQUENCE_APR_24_2013_2300)
#define MPL_X11_EMPTY_SEQUENCE_APR_24_2013_2300

#include <boost/mpl/x11/detail/size.hpp>
#include <boost/mpl/x11/iterator_tags.hpp>

namespace boost { namespace mpl { namespace x11 {

struct empty_sequence {
	struct tag;
	struct begin {
		typedef random_access_iterator_tag category;
	};
	typedef begin end;
};

namespace detail {

template <>
struct size_impl<empty_sequence::tag> {
	template <typename Sequence>
	struct apply : long_<0> {};
};

}

}}}

#endif
