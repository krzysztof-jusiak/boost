/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300

#include <boost/mpl/x11/set.hpp>
#include <boost/mpl/x11/package.hpp>
#include <boost/mpl/x11/has_key.hpp>
#include <boost/mpl/x11/is_sequence.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_policy.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_traits.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename Flags>
struct numeric_impl {
	typedef typename mpl::x11::if_<
		typename mpl::x11::is_sequence<Flags>::type,
		Flags, mpl::x11::set<Flags>
	>::type flag_set;

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

	template <
		typename Extractor, typename IntegralF, typename FractionalC
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_fractional
		>, Extractor, IntegralF, FractionalC
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <
		typename Extractor, typename IntegralF, typename SignP,
		typename FractionalC
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign,
			with_fractional
		>, Extractor, IntegralF, SignP, FractionalC
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <
		typename Extractor, typename IntegralF, typename FractionalC,
		typename ExponentC
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_fractional,
			with_exponent
		>, Extractor, IntegralF, FractionalC, ExponentC
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <
		typename Extractor, typename IntegralF, typename SignP,
		typename FractionalC, typename ExponentC
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign,
			with_fractional, with_exponent
		>, Extractor, IntegralF, SignP, FractionalC, ExponentC
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <
		typename Extractor, typename IntegralF, typename FractionalC,
		typename ExponentC, typename ExponentSignP
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_fractional,
			with_exponent, with_exponent_sign
		>, Extractor, IntegralF, FractionalC, ExponentC, ExponentSignP
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <
		typename Extractor, typename IntegralF, typename SignP,
		typename FractionalC, typename ExponentC,
		typename ExponentSignP
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign,
			with_fractional, with_exponent, with_exponent_sign
		>, Extractor, IntegralF, SignP, FractionalC, ExponentC,
		ExponentSignP
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <
		typename Extractor, typename IntegralF, typename Filter,
		typename SignP, typename FractionalC
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_filter, with_sign,
			with_fractional
		>, Extractor, IntegralF, Filter, SignP, FractionalC
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

template <typename Flags>
template <typename Extractor, typename IntegralF>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
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

	Extractor e;
	IntegralF i;
	Iterator iter(first), next(first);
	extractor_value_type c;

	while (iter != last) {
		if (!spirit::qi::parse(next, last, e, c))
			break;

		if (!i(c, attr))
			return false;
		else
			iter = next;
	}

	if (first != iter) {
		first = iter;
		return true;
	} else 
		return false;
}

template <typename Flags>
template <typename Extractor, typename IntegralF, typename Filter>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_filter
	>, Extractor, IntegralF, Filter
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	Filter filt;
	return parse(first, last, attr, filt);
}

template <typename Flags>
template <typename Extractor, typename IntegralF, typename Filter>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
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

	Extractor e;
	IntegralF i;
	Iterator iter(first), next(first);
	extractor_value_type c;
	bool v_flag(false);
	int cnt(0), rel_cnt(0);

	if (!filt(iter, last, 0))
		return 0;

	while (iter != last) {
		if (!spirit::qi::parse(next, last, e, c)) {
			if (cnt > rel_cnt) {
				if (!filt(next, last, cnt - rel_cnt))
					return false;
				else {
					rel_cnt = cnt;
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
		}

		if ((v_flag = i(c, attr))) {
			++cnt;
			iter = next;
		} else
			break;
	}

	if (cnt > rel_cnt)
		v_flag = filt(iter, last, cnt - rel_cnt);

	if (v_flag) {
		first = iter;
		return true;
	} else
		return false;
}

template <typename Flags>
template <typename Extractor, typename IntegralF, typename SignP>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign
	>, Extractor, IntegralF, SignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	using mpl::x11::has_key;
	SignP s;
	bool neg(false);
	if (!spirit::qi::parse(first, last, s, neg)) {
		if (has_key<flag_set, flag::compulsory_sign>::value)
			return false;
	}

	if (!neg) {
		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral
			>,
			Extractor, IntegralF
		> next;

		return next::parse(first, last, attr);
	} else {
		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral
			>,
			Extractor, typename IntegralF::opposite_type
		> next;

		return next::parse(first, last, attr);
	}
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename Filter, typename SignP
>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_filter, with_sign
	>, Extractor, IntegralF, Filter, SignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	Filter filt;
	return parse(first, last, attr, filt);
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename Filter, typename SignP
>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_filter, with_sign
	>, Extractor, IntegralF, Filter, SignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr, Filter &filt)
{
	using mpl::x11::has_key;
	SignP s;
	bool neg(false);
	if (!spirit::qi::parse(first, last, s, neg)) {
		if (has_key<flag_set, flag::compulsory_sign>::value)
			return false;
	}

	if (!neg) {
		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_filter
			>,
			Extractor, IntegralF, Filter
		> next;

		
		return next::parse(first, last, attr, filt);
	} else {
		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_filter
			>,
			Extractor, typename IntegralF::opposite_type, Filter
		> next;

		return next::parse(first, last, attr, filt);
	}
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename FractionalC
>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional
	>, Extractor, IntegralF, FractionalC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	using mpl::x11::has_key;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, IntegralF
	> next_int;

	typename mpl::x11::first<FractionalC>::type sep;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, typename mpl::x11::second<FractionalC>::type
	> next_frac;

	bool has_int(next_int::parse(first, last, attr));

	if (!has_int && has_key<flag_set, flag::no_leading_dot>::value)
			return false;

	if (spirit::qi::parse(first, last, sep)) {
		if (next_frac::parse(first, last, attr))
			return true;
		else
			return has_int && !has_key<
				flag_set, flag::no_trailing_dot
			>::value;
	} else
		return has_int;
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC
>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign, with_fractional
	>, Extractor, IntegralF, SignP, FractionalC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	using mpl::x11::has_key;
	SignP s;
	bool neg(false);
	if (!spirit::qi::parse(first, last, s, neg)) {
		if (has_key<flag_set, flag::compulsory_sign>::value)
			return false;
	}

	if (!neg) {
		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_fractional
			>, Extractor, IntegralF, FractionalC
		> next;

		return next::parse(first, last, attr);
	} else {
		typedef typename mpl::x11::second<
			FractionalC
		>::type FractionalF;

		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_fractional
			>, Extractor, typename IntegralF::opposite_type,
			mpl::x11::pair<
				typename mpl::x11::first<FractionalC>::type,
				typename FractionalF::opposite_type
			>
		> next;

		return next::parse(first, last, attr);
	}
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename FractionalC,
	typename ExponentC
>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional, with_exponent
	>, Extractor, IntegralF, FractionalC, ExponentC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typedef typename numeric_impl<Flags>::template apply<
	boost::mpl::x11::package<
			with_extractor, with_integral, with_fractional
		>, Extractor, IntegralF, FractionalC
	> next_num;

	typename mpl::x11::first<ExponentC>::type exp_sep;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, typename mpl::x11::second<ExponentC>::type
	> next_exp;

	if (!next_num::parse(first, last, attr))
		return false;

	if (spirit::qi::parse(first, last, exp_sep))
		return next_exp::parse(first, last, attr);
	else
		return true;
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC, typename ExponentC
>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign,
		with_fractional, with_exponent
	>, Extractor, IntegralF, SignP, FractionalC, ExponentC
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	typedef typename numeric_impl<Flags>::template apply<
	boost::mpl::x11::package<
			with_extractor, with_integral, with_sign,
			with_fractional
		>, Extractor, IntegralF, SignP, FractionalC
	> next_num;

	typename mpl::x11::first<ExponentC>::type exp_sep;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, typename mpl::x11::second<ExponentC>::type
	> next_exp;

	if (!next_num::parse(first, last, attr))
		return false;

	if (spirit::qi::parse(first, last, exp_sep))
		return next_exp::parse(first, last, attr);
	else
		return true;
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename FractionalC,
	typename ExponentC, typename ExponentSignP
>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional, with_exponent,
		with_exponent_sign
	>, Extractor, IntegralF, FractionalC, ExponentC, ExponentSignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typedef typename numeric_impl<Flags>::template apply<
	boost::mpl::x11::package<
			with_extractor, with_integral, with_fractional
		>, Extractor, IntegralF, FractionalC
	> next_num;

	typename mpl::x11::first<ExponentC>::type exp_sep;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign
		>, Extractor, typename mpl::x11::second<ExponentC>::type,
		ExponentSignP
	> next_exp;

	if (!next_num::parse(first, last, attr))
		return false;

	if (spirit::qi::parse(first, last, exp_sep))
		return next_exp::parse(first, last, attr);
	else
		return true;
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC, typename ExponentC, typename ExponentSignP
>
template <typename Iterator, typename Attribute>
bool numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign, with_fractional,
		with_exponent, with_exponent_sign
	>, Extractor, IntegralF, SignP, FractionalC, ExponentC, ExponentSignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typedef typename numeric_impl<Flags>::template apply<
	boost::mpl::x11::package<
			with_extractor, with_integral, with_sign,
			with_fractional
		>, Extractor, IntegralF, SignP, FractionalC
	> next_num;

	typename mpl::x11::first<ExponentC>::type exp_sep;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign
		>, Extractor, typename mpl::x11::second<ExponentC>::type,
		ExponentSignP
	> next_exp;

	if (!next_num::parse(first, last, attr))
		return false;

	if (spirit::qi::parse(first, last, exp_sep))
		return next_exp::parse(first, last, attr);
	else
		return true;
}

}
}}}}

#endif
