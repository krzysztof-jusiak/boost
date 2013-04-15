/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_O1_SIZE_APR_15_2013_1745)
#define MPL_X11_O1_SIZE_APR_15_2013_1745

#include <boost/mpl/x11/detail/has_size.hpp>
#include <boost/mpl/x11/sequence_fwd.hpp>
#include <boost/mpl/x11/lambda_fwd.hpp>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename Tag>
struct O1_size_impl {
	template <typename Sequence>
	struct O1_size_seq_impl : Sequence::size {};

	template <typename Sequence>
	struct apply : if_<
		has_size<Sequence>,
		O1_size_seq_impl<Sequence>,
		long_<-1>
	>::type {};
};

}

template <>
struct O1_size<> {
	template <typename T0, typename... Tn>
	struct apply : O1_size<T0> {};
};

template <typename Tag>
struct lambda<O1_size<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef O1_size<> result_;
	typedef O1_size<> type;
};

template <typename Sequence>
struct O1_size<Sequence> : detail::O1_size_impl<
	typename sequence_tag<Sequence>::type
>::template apply<Sequence> {};


}}}

#endif
