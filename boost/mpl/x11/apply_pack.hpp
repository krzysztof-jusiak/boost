/*==============================================================================
    Copyright (c) 2009      Larry Evans
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_APPLY_PACK_APR_30_2013_2300)
#define MPL_X11_APPLY_PACK_APR_30_2013_2300

#include <boost/mpl/x11/package.hpp>

namespace boost { namespace mpl { namespace x11 {

template <typename Tpack, template <typename... Un> class Op>
struct apply_pack;

template <typename... Tn, template <typename... Un> class Op>
struct apply_pack<package<Tn...>, Op> : Op<Tn...> {};

}}}

#endif
