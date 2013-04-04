/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_DETAIL_AT_APR_04_2013_1225)
#define MPL_X11_DETAIL_AT_APR_04_2013_1225

#include <boost/mpl/x11/sequence_tag_fwd.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/deref.hpp>

namespace boost { namespace mpl { namespace x11 { namespace detail {

template <typename Tag>
struct at_impl {
	template <typename Sequence, typename N>
	struct apply {
		typedef typename advance<
			typename begin<Sequence>::type, N
		>::type iter_;

		typedef typename deref<iter_>::type type;
	};
};

template <>
struct at_impl<non_sequence_tag> {};

}}}}

#endif
