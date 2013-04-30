/*==============================================================================
    Copyright (c) 2009      Larry Evans
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_PACK_INSERTER_APR_30_2013_2300)
#define MPL_X11_PACK_INSERTER_APR_30_2013_2300

namespace boost { namespace mpl { namespace x11 {

template <typename Tpack>
struct back_pack_inserter;

template <template <typename...> class Tpack, typename... Tn>
struct back_pack_inserter<Tpack<Tn...>> {
	template <typename Upack>
	struct apply;

	template <template <typename...> class Upack, typename... Un>
	struct apply<Upack<Un...>> {
		typedef Tpack<Tn..., Un...> type;
	};
};

}}}

#endif
