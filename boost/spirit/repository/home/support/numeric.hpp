//  Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_REPOSITORY_SUPPORT_NUMERIC_MAR_29_2013_2300)
#define BOOST_SPIRIT_REPOSITORY_SUPPORT_NUMERIC_MAR_29_2013_2300

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/terminal.hpp>

namespace boost { namespace spirit { namespace repository
{

BOOST_SPIRIT_DEFINE_TERMINALS_NAME_EX(
	( ushort_, ushort_type )
	( ulong_, ulong_type )
	( uint_, uint_type )
	( short_, short_type )
	( long_, long_type )
	( int_, int_type )
	( ulong_long, ulong_long_type )
	( long_long, long_long_type )
	( float_, float_type )
	( double_, double_type )
	( long_double, long_double_type )
);

}}}

#endif
