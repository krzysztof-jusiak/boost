/*==============================================================================
    Copyright (c) 2009      Larry Evans
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_TRANSFORM_PACK_APR_30_2013_2300)
#define MPL_X11_TRANSFORM_PACK_APR_30_2013_2300

#include <boost/mpl/x11/pack_inserter.hpp>
#include <boost/mpl/x11/package.hpp>
#include <boost/mpl/x11/apply.hpp>

namespace boost { namespace mpl { namespace x11 {

template <
	typename Sequence, typename Op,
	typename Inserter = back_pack_inserter<package<>>
> struct transform1_pack;

template <
	template <typename... > class Sequence, typename... Tn,
	typename Op, typename Inserter
> struct transform1_pack<Sequence<Tn...>, Op, Inserter> {
	typedef package<typename apply<Op, Tn>::type...> elements_;
        typedef typename Inserter::template apply<elements_>::type type;
};

template <
	typename Sequence0, typename Sequence1, typename Op,
	typename Inserter = back_pack_inserter<package<>>
> struct transform2_pack;

template <
	template <typename...> class Sequence0, typename... Tn,
	template <typename...> class Sequence1, typename... Un,
	typename Op, typename Inserter
> struct transform2_pack<Sequence0<Tn...>, Sequence1<Un...>, Op, Inserter> {
	typedef package<typename apply<Op, Tn, Un>::type...> elements_;
	typedef typename Inserter::template apply<elements_>::type type;
};

}}}

#endif
