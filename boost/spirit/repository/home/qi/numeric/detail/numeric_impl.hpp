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

		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr,
			Filter &filt
		);
	};

	template <typename Extractor, typename IntegralF, typename SignP>
	struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign
		>, Extractor, IntegralF, SignP
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <
		typename Extractor, typename IntegralF, typename Filter,
		typename SignP
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_filter, with_sign
		>, Extractor, IntegralF, Filter, SignP
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);

		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr,
			Filter &filt
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
			return false;
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
	Filter filt;
	return parse(first, last, attr, filt);
}

template <typename Extractor, typename IntegralF, typename Filter>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_filter
	>, Extractor, IntegralF, Filter
>::parse(Iterator &first, Iterator const &last, Attribute &attr, Filter &filt)
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
					cnt = 0;
					if (next == iter) {
						v_flag = true;
						break;
					} else {
						iter = next;
						continue;
					}
				}
			} else
				break;
		} else
			++cnt;

		if ((v_flag = i(c, v)))
			iter = next;
		else
			break;
	}

	if (cnt)
		v_flag = filt(iter, last, cnt);

	if (v_flag) {
		spirit::traits::assign_to(v, attr);
		first = iter;
	}

	return v_flag;
}

template <typename Extractor, typename IntegralF, typename SignP>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign
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

	if (neg) {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral
			>,
			Extractor, typename IntegralF::opposite_type
		> next;

		if (next::parse(iter, last, attr)) {
			first = iter;
			return true;
		}
	} else {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral
			>,
			Extractor, IntegralF
		> next;

		if (next::parse(iter, last, attr)) {
			first = iter;
			return true;
		}
	}

	return false;
}

template <
	typename Extractor, typename IntegralF, typename Filter, typename SignP
>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_filter, with_sign
	>, Extractor, IntegralF, Filter, SignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	Filter filt;
	return parse(first, last, attr, filt);
}

template <
	typename Extractor, typename IntegralF, typename Filter, typename SignP
>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_filter, with_sign
	>, Extractor, IntegralF, Filter, SignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr, Filter &filt)
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

	if (neg) {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_filter
			>,
			Extractor, typename IntegralF::opposite_type,
			Filter
		> next;

		if (next::parse(iter, last, attr, filt)) {
			first = iter;
			return true;
		}
	} else {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_filter
			>,
			Extractor, IntegralF, Filter
		> next;

		if (next::parse(iter, last, attr, filt)) {
			first = iter;
			return true;
		}
	}

	return false;
}

}
}}}}

#endif
