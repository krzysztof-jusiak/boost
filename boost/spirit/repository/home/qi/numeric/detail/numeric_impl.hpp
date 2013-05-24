/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300

#include <boost/spirit/repository/home/qi/numeric/numeric_policy.hpp>
#include <boost/mpl/x11/package.hpp>
#include <boost/mpl/x11/print.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

struct numeric_impl {
	template <typename...>
	struct apply;

	template <typename Extractor, typename IntegralF>
	struct apply<
		boost::mpl::x11::package<with_extractor, with_integral>,
		Extractor, IntegralF
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <typename Extractor, typename IntegralF, typename Filter>
	struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_filter
		>, Extractor, IntegralF, Filter
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <typename Extractor, typename IntegralF, typename SignP>
	struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign<false>
		>, Extractor, IntegralF, SignP
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <typename Extractor, typename IntegralF, typename SignP>
	struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign<true>
		>, Extractor, IntegralF, SignP
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};
};

template <typename Extractor, typename IntegralF>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral
	>, Extractor, IntegralF
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	typedef typename spirit::result_of::compile<
		spirit::qi::domain, Extractor
	>::type extractor_expr_type;
	typedef typename spirit::traits::attribute_of<
		extractor_expr_type, spirit::unused_type, Iterator
	>::type extractor_value_type;
	typedef typename spirit::traits::attribute_type<
		Attribute
	>::type attribute_type;

	Extractor e;
	IntegralF i;
	Iterator iter(first), next(first);
	extractor_value_type c;
	attribute_type v(traits::zero<attribute_type>());

	while (iter != last) {
		if (!spirit::qi::parse(next, last, e, c))
			break;

		if (!i(c, v))
			break;
		else
			iter = next;
	}

	if (first != iter) {
		spirit::traits::assign_to(v, attr);
		first = iter;
		return true;
	} else 
		return false;
}

template <typename Extractor, typename IntegralF, typename Filter>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_filter
	>, Extractor, IntegralF, Filter
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	typedef typename spirit::result_of::compile<
		spirit::qi::domain, Extractor
	>::type extractor_expr_type;
	typedef typename spirit::traits::attribute_of<
		extractor_expr_type, spirit::unused_type, Iterator
	>::type extractor_value_type;
	typedef typename spirit::traits::attribute_type<
		Attribute
	>::type attribute_type;

	Extractor e;
	IntegralF i;
	Filter filt;
	Iterator iter(first), next(first);
	extractor_value_type c;
	attribute_type v(traits::zero<attribute_type>());
	bool v_flag(false);
	int cnt(0);

	if (!filt(iter, last, 0))
		return false;

	while (iter != last) {
		if (!spirit::qi::parse(next, last, e, c)) {
			if (cnt > 0) {
				if (!filt(next, last, cnt))
					return false;
				else {
					if (next == iter) {
						v_flag = true;
						break;
					} else {
						cnt = 0;
						iter = next;
						continue;
					}
				}
			} else
				break;
		} else
			++cnt;

		
		if (!i(c, v)) {
			v_flag = (first != iter);
			break;
		} else
			iter = next;
	}

	if (v_flag)
		spirit::traits::assign_to(v, attr);

	return v_flag;
}

template <typename Extractor, typename IntegralF, typename SignP>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign<false>
	>, Extractor, IntegralF, SignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	typedef typename spirit::result_of::compile<
		spirit::qi::domain, Extractor
	>::type extractor_expr_type;
	typedef typename spirit::traits::attribute_of<
		extractor_expr_type, spirit::unused_type, Iterator
	>::type extractor_value_type;
	typedef typename spirit::traits::attribute_type<
		Attribute
	>::type attribute_type;

	SignP s;
	Iterator iter(first);
	bool neg(false);
	spirit::qi::parse(iter, last, s, neg);

	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<with_extractor, with_integral>,
		Extractor, IntegralF
	> next;

	if (next::parse(iter, last, attr)) {
		if (neg)
			traits::negate(attr);

		first = iter;
		return true;
	} else
		return false;
}

template <typename Extractor, typename IntegralF, typename SignP>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign<true>
	>, Extractor, IntegralF, SignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	typedef typename spirit::result_of::compile<
		spirit::qi::domain, Extractor
	>::type extractor_expr_type;
	typedef typename spirit::traits::attribute_of<
		extractor_expr_type, spirit::unused_type, Iterator
	>::type extractor_value_type;
	typedef typename spirit::traits::attribute_type<
		Attribute
	>::type attribute_type;

	SignP s;
	Iterator iter(first);
	bool neg(false);
	if (!spirit::qi::parse(iter, last, s, neg))
		return false;

	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<with_extractor, with_integral>,
		Extractor, IntegralF
	> next;

	if (next::parse(iter, last, attr)) {
		if (neg)
			traits::negate(attr);

		first = iter;
		return true;
	} else
		return false;
}

}
}}}}

#endif
