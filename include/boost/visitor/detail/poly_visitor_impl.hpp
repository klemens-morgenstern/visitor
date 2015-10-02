//  Boost.Visitor
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_VISITOR_DETAIL_POLY_VISITOR_IMPL_HPP_
#define BOOST_VISITOR_DETAIL_POLY_VISITOR_IMPL_HPP_

#include <boost/visitor/detail/operator_head.hpp>

namespace boost {
namespace detail {
namespace visitor {

template<typename Return, typename ...Args>
struct polymorphic_visitor_impl {};


template<typename Return, typename T, typename ... Args>
struct polymorphic_visitor_impl<Return, T, Args...> : polymorphic_visitor_impl<Return, Args...>, operator_head<Return, T>
{
	using polymorphic_visitor_impl<Return, Args...>::operator();
	using operator_head<Return, T>::operator();
};


template<typename Return, typename T>
struct polymorphic_visitor_impl<Return, T> : operator_head<Return, T>
{
	using operator_head<Return, T>::operator();
};


template<typename Return, typename ...Args>
class const_polymorphic_visitor_impl{};

template<typename Return, typename T, typename ... Args>
struct const_polymorphic_visitor_impl<Return, T, Args...> : const_polymorphic_visitor_impl<Return, Args...>, const_operator_head<Return, T>
{
	using const_polymorphic_visitor_impl<Return, Args...>::operator();
	using const_operator_head<Return, T>::operator();
};


template<typename Return, typename T>
struct const_polymorphic_visitor_impl<Return, T> : const_operator_head<Return, T>
{
	using const_operator_head<Return, T>::operator();
};

}}}

#endif /* BOOST_VISITOR_DETAIL_POLY_VISITOR_IMPL_HPP_ */
