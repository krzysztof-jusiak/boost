/*=============================================================================
    Copyright (c) 2000-2008 Aleksey Gurtovoy
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_FOR_EACH_APR_29_2013_1700)
#define MPL_X11_FOR_EACH_APR_29_2013_1700

#include <boost/mpl/x11/next_prior.hpp>
#include <boost/mpl/x11/begin_end.hpp>
#include <boost/mpl/x11/identity.hpp>
#include <boost/mpl/x11/deref.hpp>
#include <boost/mpl/x11/apply.hpp>

#include <boost/utility/value_init.hpp>
#include <functional>

namespace boost { namespace mpl { namespace x11 {
namespace detail {

template <typename F>
inline F &unwrap(F &f, int)
{
	return f;
}

template <typename F>
inline F &unwrap(reference_wrapper<F> &f, int)
{
	return f;
}

template <typename F>
inline F &unwrap(reference_wrapper<F> const &f, int)
{
	return f;
}

template <bool done = true>
struct for_each_impl {
	template <
		typename Iterator, typename LastIterator,
		typename TransformFunc, typename F
	> static void execute(
		Iterator *, LastIterator *, TransformFunc *, F
	) {}
};

template <>
struct for_each_impl<false> {
	template <
		typename Iterator, typename LastIterator,
		typename TransformFunc, typename F
	> static void execute(
		Iterator *, LastIterator *, TransformFunc *, F f
	)
	{
		typedef typename deref<Iterator>::type item;
		typedef typename apply<TransformFunc, item>::type arg;

		value_initialized<arg> x;
		unwrap(f, 0)(get(x));

		typedef typename next<Iterator>::type iter;
		for_each_impl<
			std::is_same<iter, LastIterator>::value
		>::execute(
			static_cast<iter *>(0), static_cast<LastIterator *>(0),
			static_cast<TransformFunc *>(0), f
		);
	}
};

}

template <typename Sequence, typename TransformOp, typename F>
inline void for_each(F f, Sequence * = 0, TransformOp * = 0)
{
	typedef typename begin<Sequence>::type first;
	typedef typename end<Sequence>::type last;
	detail::for_each_impl<std::is_same<first, last>::value>::execute(
		static_cast<first *>(0), static_cast<last *>(0),
		static_cast<TransformOp *>(0), f
	);
}

template <typename Sequence, typename F>
inline void for_each(F f, Sequence * = 0)
{
	x11::for_each<Sequence, identity<>>(f);
}

}}}

#endif
