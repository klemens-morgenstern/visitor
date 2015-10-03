//  Boost.Visitor
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_VISITOR_POLYMORPHIC_FUNCTOR_VISITOR_ADAPT_HPP_
#define BOOST_VISITOR_POLYMORPHIC_FUNCTOR_VISITOR_ADAPT_HPP_

#include <boost/visitor/functor_visitor.hpp>
#include <boost/visitor/polymorphic_visitor_adapt.hpp>

namespace boost
{

template<typename Interface, typename ...Lambdas>
auto make_polymorphic_functor_visitor(Lambdas && ...args)
	-> polymorphic_visitor_adapt<detail::variant::functor_visitor<Lambdas...>, Interface>
{
	auto vis = make_functor_visitor(detail::variant::forward<Lambdas>(args)...);
	return adapt_polymorphic_visitor<Interface>(vis);
}


}
#endif /* BOOST_VISITOR_POLYMORPHIC_FUNCTOR_VISITOR_ADAPT_HPP_ */
