/*=============================================================================
    Copyright (c) 2003-2004 Aleksey Gurtovoy
    Copyright (c) 2003-2004 David Abrahams
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_INSERTER_APR_19_2013_1215)
#define MPL_X11_INSERTER_APR_19_2013_1215

#include <boost/mpl/x11/push_pop.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename Sequence, typename Operation>
struct inserter {
	typedef Sequence state;
	typedef Operation operation;
};

template <typename Sequence>
struct back_inserter : inserter<Sequence, push_back<>> {};

template <typename Sequence>
struct front_inserter : inserter<Sequence, push_front<>> {};


}}}

#endif
