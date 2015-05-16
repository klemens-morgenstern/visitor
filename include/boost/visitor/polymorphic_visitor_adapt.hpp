/*
 * polymorphic_functor_visitor.hpp
 *
 *  Created on: 06.05.2015
 *      Author: Klemens
 */

#ifndef BOOST_VISITOR_POLYMORPHIC_VISITOR_ADAPT_HPP_
#define BOOST_VISITOR_POLYMORPHIC_VISITOR_ADAPT_HPP_

#include <boost/visitor/detail/poly_visitor_adapt_impl.hpp>

namespace boost
{

template<typename Visitor, typename Abstract>
struct polymorphic_visitor_adapt : detail::visitor::polymorphic_visitor_adapt_impl_start<Visitor, Abstract>::type
{
	polymorphic_visitor_adapt(const polymorphic_visitor_adapt&) = default;
	polymorphic_visitor_adapt(Visitor& vis) : 	detail::visitor::polymorphic_visitor_adapt_impl_start<Visitor, Abstract>::type(vis) {};
};



template<typename Interface, typename Visitor>
polymorphic_visitor_adapt<Visitor, Interface> adapt_polymorphic_visitor(Visitor &vis)
{
	return {vis};
}


}
#endif /* BOOST_VISITOR_POLYMORPHIC_VISITOR_ADAPT_HPP_ */
