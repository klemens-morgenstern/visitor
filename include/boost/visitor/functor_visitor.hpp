//  Boost.Visitor
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_VISITOR_STATIC_FUNCTOR_VISITOR_HPP
#define BOOST_VISITOR_STATIC_FUNCTOR_VISITOR_HPP

#include "boost/visitor/static_visitor.hpp"
#include "boost/visitor/detail/functor_visitor_deduction.hpp"

namespace boost {


/**
 * This functions creates a lambda visitor, where the return type is deduced from the first functor.
 * @attention The first lambda can NOT be a generic lambda.
 */
template<typename ...Lambdas>
detail::visitor::functor_visitor<Lambdas...> make_functor_visitor(Lambdas && ...args) {return detail::visitor::functor_visitor<Lambdas...>(detail::visitor::forward<Lambdas>(args)...);}

/** This function constructs a functor-visitor and calls apply_visitor.
 * @attention The first lambda can NOT be a generic lambda.
 */
template<typename Variant, typename ...Lambdas>
auto apply_lambdas(Variant & var, Lambdas ... lambdas) -> typename detail::visitor::functor_visitor<Lambdas...>::return_type
{
	using Ret = typename detail::visitor::functor_visitor<Lambdas...>::return_type;
	auto vis = make_functor_visitor(detail::visitor::forward<Lambdas>(lambdas)...);
	return Ret(apply_visitor(vis, var));//type
};


/**
 * This functions creates a lambda visitor, where the return type is deduced from the first functor.
 * Unlike the automatic function, the return type can be explicitly passed as a template parameter.
 * @attention The first lambda can NOT be a generic lambda.
 */
template<typename ReturnType, typename ...Lambdas>
detail::visitor::functor_visitor_exp<ReturnType, Lambdas...> make_functor_visitor(Lambdas && ...args) {return detail::visitor::functor_visitor_exp<ReturnType, Lambdas...>(detail::visitor::forward<Lambdas>(args)...);}

/** This function constructs a functor-visitor and calls apply_visitor.
 * Unlike the automatic function, the return type can be explicitly passed as a template parameter.
 * @attention The first lambda can NOT be a generic lambda.
 */
template<typename ReturnType, typename Variant, typename ...Lambdas>
auto apply_lambdas(Variant & var, Lambdas ... lambdas) -> ReturnType
{
//	using Ret = typename detail::variant::lambda_visitor<Lambdas...>::return_type;
	auto vis = make_functor_visitor<ReturnType>(detail::visitor::forward<Lambdas>(lambdas)...);
	return ReturnType(apply_visitor(vis, var));//type
};



}



#endif /* LAMBDA_VISITOR_H_ */
