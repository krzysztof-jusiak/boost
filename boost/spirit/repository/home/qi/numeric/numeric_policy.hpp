/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_NUMERIC_POLICY_MAR_30_2013_2300)
#define SPIRIT_REPOSITORY_QI_NUMERIC_POLICY_MAR_30_2013_2300

#include <boost/mpl/x11/list.hpp>
#include <boost/integer/static_log2.hpp>

namespace boost { namespace spirit { namespace repository {
namespace traits {

template <typename T>
inline T zero()
{
	return 0;
}

}

namespace qi {

/* Policy trait tags: minimal policy must feature at least "Extractor"
 * and "Inserter" methods.
 */

/* "Extractor" produces value tokens from input stream. */
struct with_extractor {};

/* "Inserter" modifies parsed value using optionally transformed value token. */
struct with_inserter {}; 

/* "Filter" transforms values produced by extractor into values, fit for
 * consumption by inserter.
 */
struct with_filter {};

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
	with_filter,
	with_sign,
	with_fraction,
	with_exponent,
	with_special
> trait_tag_order;

template <typename... Tn>
struct default_inserter;

template <typename T>
struct default_inserter<T> {
	bool operator()(boost::optional<char> const &in, T &out, bool &valid)
	{
		if (in) {
			T ref(out);
			out = out * 10 + T(*in & 0xf);
			valid = (out >= ref);
		} else
			valid = true;

		return valid;
	}
};

}
}
}}}

#endif
