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
 * and "Inserter" methods.
 */

/* "Extractor" produces value tokens from input stream. */
struct with_extractor {};

/* "Inserter" modifies parsed value using optionally transformed value token. */
struct with_inserter {}; 

/* "Mapper" transforms values produced by extractor to make them fit for
 * inserter. Examples include removing decorations and enforcing policies.
 */
struct with_mapper {};

/* "Sign" produces boolean value indicating that final value ought to be negated.
 * It is reused for exponent sing.
 */
struct with_sign {};

/* "Fraction" identifies beginning of fractional part of the number. */
struct with_fraction {};

/* "Exponent" identifies beginning of exponent specification. */
struct with_exponent {};

/* "Special" is tried to identify presence of special values, such as Nan or
 * Inf.
 */
struct with_special {};

namespace detail {

typedef boost::mpl::x11::list<
	with_extractor,
	with_inserter,
	with_mapper,
	with_sign,
	with_fraction,
	with_exponent,
	with_special
> trait_tag_order;

}
}

namespace traits {

template <typename T>
inline T zero()
{
	return 0;
}

}
}}}

#endif
