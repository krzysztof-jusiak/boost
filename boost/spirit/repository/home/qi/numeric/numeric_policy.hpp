/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_POLICY_MAR_30_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_POLICY_MAR_30_2013_2300

#include <boost/mpl/x11/list.hpp>

namespace boost { namespace spirit { namespace repository {
namespace traits {

template <typename T>
inline T zero()
{
	return 0;
}

template <typename T>
inline void negate(T &n)
{
	n = -n;
}

}

namespace qi {

/* Policy trait tags: minimal policy must feature at least "Extractor"
 * and "Inserter" methods.
 */

/* "Extractor" produces value tokens from input stream. */
struct with_extractor {};

/* "Integral" is an attribute mutating function affecting integral part of
 * the attribute using "Extractor" supplied token.
 */
struct with_integral {}; 

/* "Filter" is a variety of special-purpose skipper function which can validate
 * and remove non-numeric "decorations" from the input stream.
 */
struct with_filter {};

/* "Sign" is a parser type which can parse the sign representing
 * tokens (parser attribute must be boolean). Modifier directive affects
 * whether sign is compulsory.
 */
struct with_sign {};

/* "Fractional" is a pair<parser, function>, whereupon parser part is
 * used to detect transition into fractional part parsing and function is
 * an attribute mutator affecting fractional part of the attribute using the
 * "Extractor" supplied token. Modifier directive affects whether integral
 * part is compulsory.
 */
struct with_fractional {};

/* "Exponent" is a pair<parser, function> analogous to "Fractional" but
 * affecting the exponent of the attribute.
 */
struct with_exponent {};

/* "Special" is a variety of special-purpose skipper function which is applied
 * after sign to the whole input to establish, whether it matches any sort
 * of special value, such as NaN or Inf.
 */
struct with_special {};

namespace detail {

typedef boost::mpl::x11::list<
	with_extractor,
	with_integral,
	with_filter,
	with_sign,
	with_fractional,
	with_exponent,
	with_special
> trait_tag_order;

template <typename T>
struct default_inserter;

template <typename T>
struct default_negative_inserter {
	typedef default_inserter<T> opposite_inserter;

	bool operator()(char in, T &out)
	{
		T ref(out);
		out = out * 10 - T(in & 0xf);
		return (out <= ref);
	}

};

template <typename T>
struct default_inserter {
	typedef default_negative_inserter<T> opposite_inserter;

	bool operator()(char in, T &out)
	{
		T ref(out);
		out = out * 10 + T(in & 0xf);
		return (out >= ref);
	}
};

}
}
}}}

#endif
