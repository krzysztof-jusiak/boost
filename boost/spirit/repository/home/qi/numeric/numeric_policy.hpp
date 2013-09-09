/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_POLICY_MAR_30_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_POLICY_MAR_30_2013_2300

#include <boost/mpl/x11/list.hpp>

namespace boost { namespace spirit { namespace repository {
namespace qi {

/* Policy trait tags: minimal policy must feature at least "Extractor"
 * and "Integral" methods.
 */

/* "Extractor" produces value tokens from input stream. */
struct with_extractor {};

/* "Integer" is an attribute mutating function affecting integral part of
 * the attribute using "Extractor" supplied token.
 */
struct with_integer {}; 

/* "Filter" is a variety of special-purpose skipper function which can validate
 * and remove non-numeric "decorations" from the input stream.
 */
struct with_filter {};

/* "Sign" is a parser type which can parse the sign representing
 * tokens (parser attribute must be boolean). Flag "compulsory_sign"
 * can be used to force a compulsory sign presence in source value.
 */
struct with_sign {};

/* "Fraction" is a pair of parser and attribute mutator function: parser
 * to match the fraction part separator, and mutator to update the attribute
 * with extracted digits.
 */
struct with_fraction {};

/* "Exponent" is a pair of parser and attribute mutator function: parser
 * to match the exponent part separator, and mutator to update the exponent
 * with extracted digits. Exponent has its own attribute (normally int) for
 * precision and performance reasons.
 */
struct with_exponent {};

/* Same as "sign", but applies only to exponent's attribute.
 */
struct with_exponent_sign {};

/* "Wrapper" specifies a type which should be used in place of actual attribute
 * type and then converted to the attribute value. "Special" is expected
 * to always return the original attribute type, disregarding the optional
 * wrapper.
 */
struct with_wrapper {};

/* "Special" is a "static" parser which is attempted before the rest of numeric
 * parser methods (apart from sign, if present) to test whether input contains
 * a predefined constant value (such as NaN or Inf).
 */
struct with_special {};

namespace detail {

typedef boost::mpl::x11::list<
	with_extractor,
	with_integer,
	with_filter,
	with_sign,
	with_fraction,
	with_exponent,
	with_exponent_sign,
	with_wrapper,
	with_special
> trait_tag_order;

}

namespace flag {
/* Flags, possibly bundled together into an mpl set, can be passed to
 * numeric_parser to alter its behavior.
 */

struct compulsory_sign {};

struct no_trailing_dot {};

struct no_leading_dot {};

struct expect_dot {};

}

}
}}}

#endif
