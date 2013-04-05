/*=============================================================================  
    Copyright (c) 2009 Larry Evans

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.

    ----------------------------------------------------------------------------
    Further modifications:
    Copyright (c) 2013 Alex Dubov <oakad@yahoo.com>
    
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(MPL_X11_FOLD_ASSOC_PACK_APR_05_2013_1800)
#define MPL_X11_FOLD_ASSOC_PACK_APR_05_2013_1800

#include <boost/mpl/x11/op_assoc.hpp>

namespace boost { namespace mpl { namespace x11 {

template <
	op_assoc OpAssoc,
	template <typename, typename>class OpBinary,
	typename State0, typename... Values
> struct fold_assoc_pack;
/**@brief
 *  Apply OpStateValue_State to each element in Values...
 *  starting with intial State, State0.
 *  Associate the applications according to OpAssoc.
 *
 *  Assume the following "aliases":
 *
 *     alias     real name
 *     -----     --------
 *     f         OpBinary
 *     z         State0
 *     x1,x2,x3  Values...
 *     f(x1,x2)  OpBinary<x1,x2>::type
 *     r         fold_assoc_pack<OpAssoc,OpBinary,State0,Values...>::type
 *     r == y    boost::is_same<r,y>
 *
 *  Then:
 *
 *     If OpAssoc==assoc_left then:
 *
 *       this template is like the haskell 
 *       foldl described on p. 116 of:
 *   
 *         http://haskell.org/definition/haskell98-report.pdf
 *   
 *       IOW:
 *
 *         r == f(f(f(z,x1),x2),x3)
 *   
 *     ElseIf OpAssoc==assoc_right then:
 *
 *       this template is like the haskell 
 *       foldr described on p. 117 of:
 *   
 *         http://haskell.org/definition/haskell98-report.pdf
 *   
 *       IOW:
 *
 *         r == f(x1,f(x2,f(x3,z)))
 *   
 */

template <
	op_assoc OpAssoc,
	template<typename, typename> class OpBinary, typename State0
> struct fold_assoc_pack<OpAssoc, OpBinary, State0> {
	typedef State0 type;
};

template <
	template <typename State, typename Value> class OpStateValue_State,
	typename State0, typename Head, typename... Tail
> struct fold_assoc_pack<
	assoc_left, OpStateValue_State, State0, Head, Tail...
> : fold_assoc_pack<
	assoc_left, OpStateValue_State,
	typename OpStateValue_State<State0, Head>::type, Tail...
> {};

template <
	template <typename Value, typename State> class OpValueState_State,
	typename State0, typename Head, typename... Tail
> struct fold_assoc_pack <
	assoc_right, OpValueState_State, State0, Head, Tail...
> : OpValueState_State <
	Head, typename fold_assoc_pack<
		assoc_right, OpValueState_State, State0, Tail...
	>::type
> {};

}}}

#endif
