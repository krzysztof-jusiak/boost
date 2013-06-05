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

/* "Integral" is an attribute mutating function affecting integral part of
 * the attribute using "Extractor" supplied token.
 */
struct with_integral {}; 

/* "Filter" is a variety of special-purpose skipper function which can validate
 * and remove non-numeric "decorations" from the input stream.
 */
struct with_filter {};

/* "Sign" is a parser type which can parse the sign representing
 * tokens (parser attribute must be boolean). Flag "compulsory_sign"
 * can be used to force a compulsory sign presence in source value.
 */
struct with_sign {};

/* "Prefix" is a parser which must match the beginning of numeric string,
 * prior to optional sign and engagement of filter.
 */
struct with_prefix {};

/* "Fractional" is a pair<parser, function>, whereupon parser part is
 * used to detect transition into fractional part parsing and function is
 * an attribute mutator affecting fractional part of the attribute using the
 * "Extractor" supplied token. Modifier directive affects whether integral
 * part is compulsory.
 */
struct with_fractional {};

/* "Exponent" is a parser responsible for producing a signed integer
 * representation of exponent. Can be defined in terms of numeric_parser
 * itself.
 */
struct with_exponent {};

/* "Special" is a variety of special-purpose skipper function which is applied
 * after sign to the whole input to establish, whether it matches any sort
 * of special value, such as NaN or Inf.
 */
struct with_special {};

/* "Flags" is a set of type tags used to affect the actual parsing logic.
 * This is a sort of duplication of spirit modifier syntax, but without
 * the need to define more specific directives.
 * This may change in the future.
 */
struct with_flags {};

namespace detail {

typedef boost::mpl::x11::list<
	with_extractor,
	with_integral,
	with_filter,
	with_sign,
	with_prefix,
	with_fractional,
	with_exponent,
	with_special,
	with_flags
> trait_tag_order;

}

namespace flag {

struct compulsory_sign {};

struct no_trailing_dot {};

struct no_leading_dot {};

struct expect_dot {};

}

}
}}}

#endif
