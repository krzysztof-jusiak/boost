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
struct has_adjust {
	template <typename U>
	static std::true_type test(
		type_wrapper<U> const volatile *,
		type_wrapper<decltype(U::adjust)> * = 0
	);

	static std::false_type test(...);

	typedef decltype(test(static_cast<type_wrapper<T> *>(nullptr))) type;

	static const bool value = type::value;
};

template <typename WrapperT, typename ValueType>
typename std::enable_if<has_adjust<WrapperT>::value, bool>::type adjust(
	WrapperT &w, ValueType &v
)
{
	return WrapperT::adjust(w, v);
}

template <typename WrapperT, typename ValueType>
typename std::enable_if<!has_adjust<WrapperT>::value, bool>::type adjust(
	WrapperT &w, ValueType &v
)
{
	return true;
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
		typename Extractor, typename IntegralF, typename SignP,
		typename PrefixP
	>
	struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign, with_prefix
		>, Extractor, IntegralF, SignP, PrefixP
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
		typename ExponentP
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_fractional,
			with_exponent
		>, Extractor, IntegralF, FractionalC, ExponentP
	> {
		template <typename Iterator, typename Attribute>
		static bool parse(
			Iterator &first, Iterator const &last, Attribute &attr
		);
	};

	template <
		typename Extractor, typename IntegralF, typename SignP,
		typename FractionalC, typename ExponentP
	> struct apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign,
			with_fractional, with_exponent
		>, Extractor, IntegralF, SignP, FractionalC, ExponentP
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

	if (first != iter && adjust(i, attr)) {
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

	Extractor e;
	IntegralF i;
	Iterator iter(first), next(first);
	extractor_value_type c;
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

		if ((v_flag = i(c, attr)))
			iter = next;
		else
			break;
	}

	if (cnt)
		v_flag = filt(iter, last, cnt);

	if (v_flag && adjust(i, attr))
		first = iter;

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
	typename Extractor, typename IntegralF, typename SignP,
	typename PrefixP
>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign, with_prefix
	>, Extractor, IntegralF, SignP, PrefixP
>::parse(Iterator &first, Iterator const &last, Attribute &attr)
{
	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_sign
		>, Extractor, IntegralF, SignP
	> next;

	PrefixP p;
	if (spirit::qi::parse(first, last, p))
		return next::parse(first, last, attr);
	else
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
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional
	>, Extractor, IntegralF, FractionalC
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typename mpl::x11::first<FractionalC>::type sep;

	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, IntegralF
	> next_int;

	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<
			with_extractor, with_integral
		>, Extractor, typename mpl::x11::second<FractionalC>::type
	> next_frac;

	if (next_int::parse(first, last, attr)) {
		if (spirit::qi::parse(first, last, sep))
			next_frac::parse(first, last, attr);

		return true;
	} else if (spirit::qi::parse(first, last, sep)) {
		if (next_frac::parse(first, last, attr))
			return true;
	}

	return false;
}

template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC
>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
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

template <
	typename Extractor, typename IntegralF, typename FractionalC,
	typename ExponentP
>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_fractional, with_exponent
	>, Extractor, IntegralF, FractionalC, ExponentP
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	typedef typename numeric_impl::apply<
		boost::mpl::x11::package<
			with_extractor, with_integral, with_fractional
		>, Extractor, IntegralF, FractionalC
	> next;

	typedef typename spirit::result_of::compile<
		spirit::qi::domain, ExponentP
	>::type exponent_expr_type;
	typedef typename spirit::traits::attribute_of<
		exponent_expr_type, spirit::unused_type, Iterator
	>::type exponent_value_type;

	if (next::parse(first, last, attr)) {
		auto e(repository::traits::zero<exponent_value_type>());
		ExponentP p;

		Iterator iter(first);
		if (spirit::qi::parse(iter, last, p, e)) {
			if (traits::scale(attr, e)) {
				first = iter;
				return true;
			}
		} else
			return iter == first;
	}

	return false;
}

template <
	typename Extractor, typename IntegralF, typename SignP,
	typename FractionalC, typename ExponentP
>
template <typename Iterator, typename Attribute>
bool numeric_impl::apply<
	boost::mpl::x11::package<
		with_extractor, with_integral, with_sign, with_fractional,
		with_exponent
	>, Extractor, IntegralF, SignP, FractionalC, ExponentP
>::parse(Iterator &first, Iterator const &last, Attribute &attr) {
	SignP s;
	bool neg(false);
	spirit::qi::parse(first, last, s, neg);

	if (!neg) {
		typedef typename numeric_impl::apply<
			boost::mpl::x11::package<
				with_extractor, with_integral, with_fractional,
				with_exponent
			>, Extractor, IntegralF, FractionalC, ExponentP
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
			>, ExponentP
		> next;

		return next::parse(first, last, attr);
	}
}

}
}}}}

#endif
