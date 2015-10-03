//  Boost.Visitor
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).


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
