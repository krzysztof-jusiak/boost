/*=============================================================================
    Copyright (c) 2013      Alex Dubov <oakad@yahoo.com>

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(SPIRIT_REPOSITORY_QI_TRAITS_MAR_30_2013_2300)
#define SPIRIT_REPOSITORY_QI_TRAITS_MAR_30_2013_2300

#include <boost/mpl/x11/list.hpp>

namespace boost { namespace spirit { namespace repository { namespace qi {

/* Trait tags */
struct with_extractor {};

struct with_mapper {};

struct with_inserter {};

struct with_sign {};

struct with_separator {};

struct enable_leading_dot {};

struct with_exponent {};

namespace detail {

typedef boost::mpl::x11::list<
	with_extractor,
	with_mapper,
	with_inserter,
	with_sign,
	with_separator,
	enable_leading_dot,
	with_exponent
> trait_tag_order;

}
}}}}

#endif
