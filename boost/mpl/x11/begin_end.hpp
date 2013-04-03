/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_BEGIN_END_APR_03_2013_1430)
#define MPL_X11_BEGIN_END_APR_03_2013_1430

#include <boost/mpl/x11/sequence_tag.hpp>
#include <boost/mpl/x11/detail/begin_end.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename Sequence>
struct begin {
	typedef typename sequence_tag<Sequence>::type tag_;
	typedef typename detail::begin_impl<tag_>
	::template apply<Sequence>::type type;
};

template <typename Sequence>
struct end {
	typedef typename sequence_tag<Sequence>::type tag_;
	typedef typename detail::end_impl<tag_>
	::template apply<Sequence>::type type;
};

}}}

#endif
