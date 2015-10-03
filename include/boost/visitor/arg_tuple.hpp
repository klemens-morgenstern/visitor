//  Boost.Visitor
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).


#ifndef BOOST_VISITOR_ARG_TUPLE_HPP_
#define BOOST_VISITOR_ARG_TUPLE_HPP_

namespace boost
{


/** A tuple of arguments.
 * This is an empty tuple so no requirements apply to the parameters.
 * It is used to create a multi-visitor.
 * @tparam Args the types.
 *
 */
template<typename ...Args>
struct arg_tuple {};


}



#endif /* BOOST_VISITOR_ARG_TUPLE_HPP_ */
