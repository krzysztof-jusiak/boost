/*=============================================================================
    Copyright (c) 2000-2004 Aleksey Gurtovoy
    Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(MPL_X11_JOINT_VIEW_APR_25_2013_2300)
#define MPL_X11_JOINT_VIEW_APR_25_2013_2300

namespace boost { namespace mpl { namespace x11 {
namespace detail {

struct joint_view_tag;

template <>
struct size_impl<joint_view_tag> {
	template <typename JointView>
	struct apply : plus<
		size<typename JointView::sequence1_>,
		size<typename JointView::sequence2_>
	> {};
};

template <typename Iterator0, typename LastIterator0, typename Iterator1>
struct joint_iter {
	typedef Iterator0 base;
	typedef forward_iterator_tag category;
};

template <typename LastIterator0, typename Iterator1>
struct joint_iter<LastIterator0, LastIterator0, Iterator1> {
	typedef Iterator1 base;
	typedef forward_iterator_tag category;
};

}

template <typename I0, typename L0, typename I1>
struct deref<detail::joint_iter<I0, L0, I1>> {
	typedef typename detail::joint_iter<I0, L0, I1>::base base_;
	typedef typename deref<base_>::type type;
};

template <typename I0, typename L0, typename I1>
struct next<detail::joint_iter<I0, L0, I1>> {
	typedef detail::joint_iter<typename next<I0>::type, L0, I1> type;
};

template<typename L0, typename I1>
struct next<detail::joint_iter<L0, L0, I1>> {
	typedef detail::joint_iter<L0, L0, typename next<I1>::type> type;
};

template <typename T0, typename T1, typename T2, typename Tag>
struct lambda<detail::joint_iter<T0, T1, T2>, Tag, long_<3>> {
	typedef false_type is_le;
	typedef detail::joint_iter<T0, T1, T2> result_;
	typedef result_ type;
};

template <typename...>
struct joint_view;

template <>
struct joint_view<> {
	template <typename T0, typename T1, typename... Tn>
	struct apply : joint_view<T0, T1> {};
};

template <typename Tag>
struct lambda<joint_view<>, Tag, long_<-1>> {
	typedef false_type is_le;
	typedef joint_view<> result_;
	typedef joint_view<> type;
};
template <typename Sequence1_, typename Sequence2_>
struct joint_view<Sequence1_, Sequence2_> {
	typedef typename begin<Sequence1_>::type first1_;
	typedef typename end<Sequence1_>::type last1_;
	typedef typename begin<Sequence2_>::type first2_;
	typedef typename end<Sequence2_>::type last2_;

	typedef Sequence1_ sequence1_;
	typedef Sequence2_ sequence2_;

	typedef joint_view type;
	typedef detail::joint_view_tag tag;
	typedef detail::joint_iter<first1_, last1_, first2_> begin;
	typedef detail::joint_iter<last1_, last1_, last2_> end;
};

}}}

#endif
