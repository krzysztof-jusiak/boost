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
		static int parse(
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
		static int parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);

		template <typename Iterator, typename Attribute>
		static int parse(
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
		static int parse(
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
		static int parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);

		template <typename Iterator, typename Attribute>
		static int parse(
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
		static int parse(
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
		static int parse(
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
		static int parse(
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
		static int parse(
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
		static int parse(
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
		static int parse(
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
		static int parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);

		template <typename Iterator, typename Attribute>
		static int parse(
			Iterator &first, Iterator const &last, Attribute &attr,
			Filter &filt
		);
	};
};

template <typename Flags>
template <typename Extractor, typename IntegralF>
template <typename Iterator, typename Attribute>
int numeric_impl<Flags>::apply<
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
	int cnt(0);

	while (iter != last) {
		if (!spirit::qi::parse(next, last, e, c))
			break;

		if (!i(c, attr))
			return 0;
		else {
			++cnt;
			iter = next;
		}
	}

	if (first != iter) {
		first = iter;
		return cnt;
	} else 
		return 0;
}

template <typename Flags>
template <typename Extractor, typename IntegralF, typename Filter>
template <typename Iterator, typename Attribute>
int numeric_impl<Flags>::apply<
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
int numeric_impl<Flags>::apply<
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
					return 0;
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
		return cnt;
	} else
		return 0;
}

template <typename Flags>
template <typename Extractor, typename IntegralF, typename SignP>
template <typename Iterator, typename Attribute>
int numeric_impl<Flags>::apply<
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
			return 0;
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
int numeric_impl<Flags>::apply<
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
int numeric_impl<Flags>::apply<
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
			return 0;
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
int numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional
	>, Extractor, IntegralF, FractionalC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
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

	int cnt(next_int::parse(first, last, attr));

	if (cnt) {
		if (spirit::qi::parse(first, last, sep)) {
			int f_cnt(next_frac::parse(first, last, attr));
			if (f_cnt)
				return cnt + f_cnt;
		}

		return cnt;
	} else if (spirit::qi::parse(first, last, sep))
		return next_frac::parse(first, last, attr);

	return 0;
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC
>
template <typename Iterator, typename Attribute>
int numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign, with_fractional
	>, Extractor, IntegralF, SignP, FractionalC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	using mpl::x11::has_key;
	SignP s;
	bool neg(false);
	if (!spirit::qi::parse(first, last, s, neg)) {
		if (has_key<flag_set, flag::compulsory_sign>::value)
			return 0;
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
int numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional, with_exponent
	>, Extractor, IntegralF, FractionalC, ExponentC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, IntegralF
	> next_int;
	typename mpl::x11::first<FractionalC>::type frac_sep;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, typename mpl::x11::second<FractionalC>::type
	> next_frac;

	typename mpl::x11::first<ExponentC>::type exp_sep;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, typename mpl::x11::second<ExponentC>::type
	> next_exp;

	int cnt(next_int::parse(first, last, attr)), f_cnt(0);
	bool has_int(false), has_frac(false);
	using mpl::x11::has_key;

	if (cnt)
		has_int = true;
	else if (has_key<flag_set, flag::no_leading_dot>::value)
		return 0;

	if (spirit::qi::parse(first, last, frac_sep)) {
		f_cnt = next_frac::parse(first, last, attr);
		if (f_cnt)
			has_frac = true;
		else if (has_key<flag_set, flag::no_trailing_dot>::value)
			return 0;
	}

	if (!has_int && !has_frac)
		return 0;

	if (spirit::qi::parse(first, last, exp_sep)) {
		int exp(0), e_cnt(0);
		if (0 < (e_cnt = next_exp::parse(first, last, exp))) {
			if (traits::scale(attr, exp - f_cnt))
				return cnt + f_cnt + e_cnt;
			else
				return 0;
		}
	} else
		return traits::scale(attr, -f_cnt) ? cnt + f_cnt : 0;

	return 0;
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC, typename ExponentC
>
template <typename Iterator, typename Attribute>
int numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign,
		with_fractional, with_exponent
	>, Extractor, IntegralF, SignP, FractionalC, ExponentC
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	using mpl::x11::has_key;
	SignP s;
	bool neg(false);
	if (!spirit::qi::parse(first, last, s, neg)) {
		if (has_key<flag_set, flag::compulsory_sign>::value)
			return 0;
	}

	if (!neg) {
		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_fractional,
				with_exponent
			>, Extractor, IntegralF, FractionalC, ExponentC
		> next;

		return next::parse(first, last, attr);
	} else {
		typedef typename mpl::x11::second<
			FractionalC
		>::type FractionalF;

		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_fractional,
				with_exponent
			>, Extractor, typename IntegralF::opposite_type,
			mpl::x11::pair<
				typename mpl::x11::first<FractionalC>::type,
				typename FractionalF::opposite_type
			>, ExponentC
		> next;

		return next::parse(first, last, attr);
	}
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename FractionalC,
	typename ExponentC, typename ExponentSignP
>
template <typename Iterator, typename Attribute>
int numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional, with_exponent,
		with_exponent_sign
	>, Extractor, IntegralF, FractionalC, ExponentC, ExponentSignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, IntegralF
	> next_int;
	int const int_base_scale = IntegralF::base_scale;

	typename mpl::x11::first<FractionalC>::type frac_sep;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, typename mpl::x11::second<FractionalC>::type
	> next_frac;
	int const frac_base_scale = mpl::x11::second<FractionalC>::type::base_scale;

	typename mpl::x11::first<ExponentC>::type exp_sep;

	typedef typename numeric_impl<Flags>::template apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign
		>, Extractor, typename mpl::x11::second<ExponentC>::type,
		ExponentSignP
	> next_exp;

	int cnt(next_int::parse(first, last, attr)), f_cnt(0), base_scale(frac_base_scale);
	bool has_int(false), has_frac(false);
	using mpl::x11::has_key;

	if (cnt)
		has_int = true;
	else if (has_key<flag_set, flag::no_leading_dot>::value)
		return 0;

	if (int_base_scale != frac_base_scale) {
		if (!traits::scale(attr, frac_base_scale - int_base_scale + 1))
			return false;
	}

	if (spirit::qi::parse(first, last, frac_sep)) {
		f_cnt = next_frac::parse(first, last, attr);
		if (f_cnt)
			has_frac = true;
		else if (has_key<flag_set, flag::no_trailing_dot>::value)
			return 0;
	}

	if (!has_int && !has_frac)
		return 0;

	std::cout << "attr " << attr << '\n';
	if (spirit::qi::parse(first, last, exp_sep)) {
		int exp(0), e_cnt(0);
		if (0 < (e_cnt = next_exp::parse(first, last, exp))) {
			printf("exp %d, f_cnt %d, base %d\n", exp, f_cnt, base_scale);
			return traits::scale(attr, exp - f_cnt - base_scale)
			       ? cnt + f_cnt + e_cnt : 0;
		}
	} else
		return traits::scale(attr, -f_cnt - base_scale) ? cnt + f_cnt : 0;

	return 0;
}

template <typename Flags>
template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC, typename ExponentC, typename ExponentSignP
>
template <typename Iterator, typename Attribute>
int numeric_impl<Flags>::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign, with_fractional,
		with_exponent, with_exponent_sign
	>, Extractor, IntegralF, SignP, FractionalC, ExponentC, ExponentSignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	using mpl::x11::has_key;
	SignP s;
	bool neg(false);
	if (!spirit::qi::parse(first, last, s, neg)) {
		if (has_key<flag_set, flag::compulsory_sign>::value)
			return 0;
	}

	if (!neg) {
		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_fractional,
				with_exponent, with_exponent_sign
			>, Extractor, IntegralF, FractionalC, ExponentC,
			ExponentSignP
		> next;

		return next::parse(first, last, attr);
	} else {
		typedef typename mpl::x11::second<
			FractionalC
		>::type FractionalF;

		typedef typename numeric_impl<Flags>::template apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_fractional,
				with_exponent, with_exponent_sign
			>, Extractor, typename IntegralF::opposite_type,
			mpl::x11::pair<
				typename mpl::x11::first<FractionalC>::type,
				typename FractionalF::opposite_type
			>, ExponentC, ExponentSignP
		> next;

		return next::parse(first, last, attr);
	}
}

}
}}}}

#endif
