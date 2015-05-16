/*
 * polymorphic_visitor.hpp
 *
 *  Created on: 06.05.2015
 *      Author: Klemens
 */

#ifndef BOOST_VISITOR_POLYMORPHIC_VISITOR_HPP_
#define BOOST_VISITOR_POLYMORPHIC_VISITOR_HPP_

#include <boost/visitor/detail/poly_visitor_impl.hpp>
#include <boost/visitor/static_visitor.hpp>

namespace boost
{

//i dislike using "static_visitor" but this is needed for boost::variant. maybe this can be changed to a general declaration.
template<typename Return, typename ...Args>
struct polymorphic_visitor : static_visitor<Return>, detail::visitor::polymorphic_visitor_impl<Return, Args...>
{
	using detail::visitor::polymorphic_visitor_impl<Return, Args...>::operator();
};

//i dislike using "static_visitor" but this is needed for boost::variant. maybe this can be changed to a general declaration.
template<typename Return, typename ...Args>
struct const_polymorphic_visitor : static_visitor<Return>, detail::visitor::const_polymorphic_visitor_impl<Return, Args...>
{
	using detail::visitor::const_polymorphic_visitor_impl<Return, Args...>::operator();
};

}
#endif /* BOOST_VISITOR_POLYMORPHIC_VISITOR_HPP_ */
