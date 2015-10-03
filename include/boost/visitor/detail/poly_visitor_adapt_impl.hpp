//  Boost.Visitor
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).


#ifndef BOOST_VISITOR_DETAIL_POLY_VISITOR_ADAPT_IMPL_HPP_
#define BOOST_VISITOR_DETAIL_POLY_VISITOR_ADAPT_IMPL_HPP_

#include <boost/visitor/detail/operator_adapt_head.hpp>

namespace boost {
namespace detail {
namespace visitor {

template<typename Visitor, typename Abstract>
struct end_abstract : Abstract
{
	Visitor &vis;
	end_abstract(Visitor &vis) : vis(vis) {};
	end_abstract(const end_abstract&) = default;

};

template<typename Visitor, typename Abstract, typename ...Args>
struct polymorphic_visitor_adapt_impl
{

};


template<typename Visitor, typename Abstract, typename T, typename ... Args>
struct polymorphic_visitor_adapt_impl<Visitor, Abstract, T, Args...> : operator_adapt_head<Visitor, polymorphic_visitor_adapt_impl<Visitor, Abstract, Args...>, T>
{
	polymorphic_visitor_adapt_impl(const polymorphic_visitor_adapt_impl&) = default;
	polymorphic_visitor_adapt_impl(Visitor& vis)
			: operator_adapt_head<Visitor, polymorphic_visitor_adapt_impl<Visitor, Abstract, Args...>, T>(vis) {};
};


template<typename Visitor, typename Abstract, typename T>
struct polymorphic_visitor_adapt_impl<Visitor, Abstract, T> : operator_adapt_head<Visitor, end_abstract<Visitor, Abstract>, T>
{
	polymorphic_visitor_adapt_impl(const polymorphic_visitor_adapt_impl&) = default;
	polymorphic_visitor_adapt_impl(Visitor& vis)
			: operator_adapt_head<Visitor, end_abstract<Visitor, Abstract>, T>(vis) {};
};


template<typename Visitor, typename Abstract, typename ...Args>
class const_polymorphic_visitor_adapt_impl{};

template<typename Visitor, typename Abstract, typename T, typename ... Args>
struct const_polymorphic_visitor_adapt_impl<Visitor, Abstract, T, Args...> : const_operator_adapt_head<Visitor, const_polymorphic_visitor_adapt_impl<Visitor, Abstract, Args...>, T>
{
	const_polymorphic_visitor_adapt_impl(const const_polymorphic_visitor_adapt_impl&) = default;
	const_polymorphic_visitor_adapt_impl(Visitor& vis)
			: const_operator_adapt_head<Visitor, const_polymorphic_visitor_adapt_impl<Visitor, Abstract, Args...>, T>(vis) {};
};


template<typename Visitor, typename Abstract, typename T>
struct const_polymorphic_visitor_adapt_impl<Visitor, Abstract, T> : const_operator_adapt_head<Visitor, end_abstract<Visitor, Abstract>, T>
{
	const_polymorphic_visitor_adapt_impl(const const_polymorphic_visitor_adapt_impl&) = default;
	const_polymorphic_visitor_adapt_impl(Visitor& vis)
			: const_operator_adapt_head<Visitor, end_abstract<Visitor, Abstract>, T>(vis) {};
};


template<typename Visitor, typename Abstract>
struct polymorphic_visitor_adapt_impl_start {};

template<typename Visitor, typename Ret, typename ...Args>
struct polymorphic_visitor_adapt_impl_start<Visitor, polymorphic_visitor<Ret, Args...>>
{
	using type = polymorphic_visitor_adapt_impl<Visitor, polymorphic_visitor<Ret, Args...>, Args...>;
};


template<typename Visitor, typename Ret, typename ...Args>
struct polymorphic_visitor_adapt_impl_start<Visitor, const_polymorphic_visitor<Ret, Args...>>
{
	using type = const_polymorphic_visitor_adapt_impl<Visitor, const_polymorphic_visitor<Ret, Args...>, Args...>;
};

}}}

#endif /* BOOST_VISITOR_DETAIL_POLY_VISITOR_IMPL_HPP_ */
