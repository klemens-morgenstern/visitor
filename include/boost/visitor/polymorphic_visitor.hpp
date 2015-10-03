//  Boost.Variant
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).


#ifndef BOOST_VISITOR_POLYMORPHIC_VISITOR_HPP_
#define BOOST_VISITOR_POLYMORPHIC_VISITOR_HPP_

#include <boost/visitor/detail/poly_visitor_impl.hpp>
#include <boost/visitor/static_visitor.hpp>

namespace boost
{

/** A polymorphic visitor is a class which defines an abstract polymorphic interface.
 * This can then be implemented or created via adaptation.
 *
 * If the visitor shall accept more than one argument, the @ref arg_tuple can be used.
 * @tparam Return the return type of the operations
 * @tparam Args the arguments
 *
 */


//i dislike using "static_visitor" but this is needed for boost::variant. maybe this can be changed to a general declaration.
template<typename Return, typename ...Args>
struct polymorphic_visitor : static_visitor<Return>, detail::visitor::polymorphic_visitor_impl<Return, Args...>
{
	using detail::visitor::polymorphic_visitor_impl<Return, Args...>::operator();
	virtual ~polymorphic_visitor() = default;
};

/** A polymorphic visitor is a class which defines an abstract polymorphic interface.
 * This can then be implemented or created via adaptation.
 * Unlike @ref polymorphic_visitor, this calls are implemented as const member function.
 * If the visitor shall accept more than one argument, the @ref arg_tuple can be used.
 * @tparam Return the return type of the operations
 * @tparam Args the arguments
 *
 */
//i dislike using "static_visitor" but this is needed for boost::variant. maybe this can be changed to a general declaration.
template<typename Return, typename ...Args>
struct const_polymorphic_visitor : static_visitor<Return>, detail::visitor::const_polymorphic_visitor_impl<Return, Args...>
{
	using detail::visitor::const_polymorphic_visitor_impl<Return, Args...>::operator();
	virtual ~const_polymorphic_visitor() = default;
};

}
#endif /* BOOST_VISITOR_POLYMORPHIC_VISITOR_HPP_ */
