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

	template <typename Extractor, typename Inserter>
	struct apply<
		boost::mpl::x11::package<with_extractor, with_inserter>,
		Extractor, Inserter
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <typename Extractor, typename Inserter, typename Filter>
	struct apply<
		boost::mpl::x11::package<
			with_extractor, with_inserter, with_filter
		>, Extractor, Inserter, Filter
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};
};

template <typename Extractor, typename Inserter>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_inserter
	>, Extractor, Inserter
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
	Inserter i;
	Iterator save(first), iter(first);
	extractor_value_type c;
	attribute_type v(traits::zero<attribute_type>());
	bool v_flag(false);

	while (iter != last) {
		if (!spirit::qi::parse(iter, last, e, c))
			break;

		if (i(optional<extractor_value_type>(c), v, v_flag)) {
			first = iter;
			continue;
		} else
			break;
	}

	if (v_flag)
		spirit::traits::assign_to(v, attr);
	else
		first = save;

	return v_flag;
}

template <typename Extractor, typename Inserter, typename Filter>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_inserter, with_filter
	>, Extractor, Inserter, Filter
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
	Inserter i;
	Filter filt;
	Iterator save(first), iter(first);
	extractor_value_type c_in;
	optional<extractor_value_type> c_out;
	attribute_type v(traits::zero<attribute_type>());
	bool v_flag(false);

	while (iter != last) {
		if (!spirit::qi::parse(iter, last, e, c_in))
			break;

		if (filt(c_in, c_out) && i(c_out, v, v_flag)) {
			first = iter;
			continue;
		} else
			break;
	}

	if (v_flag)
		spirit::traits::assign_to(v, attr);
	else
		first = save;

	return v_flag;
}

}
}}}}

#endif
