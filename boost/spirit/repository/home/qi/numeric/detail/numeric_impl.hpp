/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_IMPL_MAR_29_2013_2300

#include <boost/mpl/x11/package.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_policy.hpp>
#include <boost/spirit/repository/home/qi/numeric/numeric_traits.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {
namespace detail {

template <typename T>
struct type_wrapper {
	typedef T type;
};

template <typename T>
struct has_scale {
	template <typename U>
	static std::true_type test(
		type_wrapper<U> const volatile *,
		type_wrapper<decltype(U::scale)> * = 0
	);

	static std::false_type test(...);

	typedef decltype(test(static_cast<type_wrapper<T> *>(nullptr))) type;

	static const bool value = type::value;
};

template <typename FunctorT, typename ValueType>
typename std::enable_if<has_scale<FunctorT>::value, bool>::type scale(
	ValueType &v, int exponent
)
{
	return FunctorT::scale(v, exponent);
}

template <typename FunctorT, typename ValueType>
typename std::enable_if<!has_scale<FunctorT>::value, bool>::type scale(
	FunctorT &f, ValueType &v, int exponent
)
{
	return traits::scale(v, exponent);
}

struct numeric_impl {
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

template <typename Extractor, typename IntegralF>
template <typename Iterator, typename Attribute>
int numeric_impl::apply<
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

template <typename Extractor, typename IntegralF, typename Filter>
template <typename Iterator, typename Attribute>
int numeric_impl::apply<
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
int numeric_impl::apply<
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

template <typename Extractor, typename IntegralF, typename SignP>
template <typename Iterator, typename Attribute>
int numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign
	>, Extractor, IntegralF, SignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	SignP s;
	bool neg(false);
	spirit::qi::parse(first, last, s, neg);

	if (!neg) {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral
			>,
			Extractor, IntegralF
		> next;

		return next::parse(first, last, attr);
	} else {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral
			>,
			Extractor, typename IntegralF::opposite_type
		> next;

		return next::parse(first, last, attr);
	}
}

template <
	typename Extractor, typename IntegralF, typename Filter, typename SignP
>
template <typename Iterator, typename Attribute>
int numeric_impl::apply<
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
int numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_filter, with_sign
	>, Extractor, IntegralF, Filter, SignP
>::parse(Iterator &first, Iterator const &last, Attribute &attr, Filter &filt)
{
	SignP s;
	bool neg(false);
	spirit::qi::parse(first, last, s, neg);

	if (!neg) {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_filter
			>,
			Extractor, IntegralF, Filter
		> next;

		
		return next::parse(first, last, attr, filt);
	} else {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_filter
			>,
			Extractor, typename IntegralF::opposite_type, Filter
		> next;

		return next::parse(first, last, attr, filt);
	}
}

template <
	typename Extractor, typename IntegralF, typename FractionalC
>
template <typename Iterator, typename Attribute>
int numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional
	>, Extractor, IntegralF, FractionalC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, IntegralF
	> next_int;

	typename mpl::x11::first<FractionalC>::type sep;

	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, typename mpl::x11:second<FractionalC>::type
	> next_frac;

	int cnt(next_int::parse(first, last, attr));

	if (cnt) {
		if (spirit::qi::parse(first, last, sep)) {
			int f_cnt(next_frac::parse(first, last, attr));
			if (f_cnt)
				return scale(attr, -f_cnt) ? cnt + f_cnt : 0;
		}

		return cnt;
	} else if (spirit::qi::parse(first, last, sep)) {
		if ((cnt = next_frac::parse(first, last, attr)))
			return scale(attr, -cnt) ? cnt : 0;
	}

	return 0;
}

template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC
>
template <typename Iterator, typename Attribute>
int numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign, with_fractional
	>, Extractor, IntegralF, SignP, FractionalC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	SignP s;
	bool neg(false);
	spirit::qi::parse(first, last, s, neg);

	if (!neg) {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_fractional
			>, Extractor, IntegralF, FractionalC
		> next;

		return next::parse(first, last, attr);
	} else {
		typedef typename mpl::x11::second<
			FractionalC
		>::type FractionalF;

		typedef typename numeric_impl::apply<
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

template <typename ExponentC>
template <typename Iterator, typename Attribute>
int numeric_impl::apply<
	boost::mpl::x11::package<with_exponent>, ExponentC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typename mpl::x11::first<ExponentC>::type sep;
	typename mpl::x11::second<ExponentC>::type val;



}

template <
	typename Extractor, typename IntegralF, typename FractionalC,
	typename ExponentC
>
template <typename Iterator, typename Attribute>
int numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional, with_exponent
	>, Extractor, IntegralF, FractionalC, ExponentC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, IntegralF
	> next_int;

	typename mpl::x11::first<FractionalC>::type sep;

	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, typename mpl::x11:second<FractionalC>::type
	> next_frac;

	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<with_exponent>, ExponentC
	> next_exp;

	int cnt(next_int::parse(first, last, attr));

	if (cnt) {
		if (spirit::qi::parse(first, last, sep)) {
			int f_cnt(next_frac::parse(first, last, attr));
			if (f_cnt) {
				int exp(0);
				int e_cnt(next_exp::parse(first, last, exp));
				return scale(attr, exp - f_cnt)
				       ? cnt + f_cnt + e_cnt : 0;
			}
		}

		return cnt;
	} else if (spirit::qi::parse(first, last, sep)) {
		if ((cnt = next_frac::parse(first, last, attr))) {
			int exp(0);
			int e_cnt(next_exp::parse(first, last, exp));
			return scale(attr, exp - cnt)
			       ? cnt + e_cnt : 0;
		}
	}

	return 0;
}

template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC, typename ExponentC
>
template <typename Iterator, typename Attribute>
int numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign, with_fractional,
		with_exponent
	>, Extractor, IntegralF, SignP, FractionalC, ExponentC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	SignP s;
	bool neg(false);
	spirit::qi::parse(first, last, s, neg);

	if (!neg) {
		typedef typename numeric_impl::apply<
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

		typedef typename numeric_impl::apply<
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

}
}}}}

#endif
