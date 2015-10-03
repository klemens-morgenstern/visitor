//  Boost.Visitor
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_VISITOR_DETAIL_OPERATOR_HEAD_HPP_
#define BOOST_VISITOR_DETAIL_OPERATOR_HEAD_HPP_

#include <boost/visitor/arg_tuple.hpp>

namespace boost {
namespace detail {
namespace visitor {

template<typename Return, typename T>
struct operator_head
{
	virtual Return operator()(T)  = 0;
};

template<typename Return, typename ...Args>
struct operator_head<Return, arg_tuple<Args...>>
{
	virtual Return operator()(Args...) = 0;
};

template<typename Return, typename T>
struct const_operator_head
{
	virtual Return operator()(T) const = 0;
};

template<typename Return, typename ...Args>
struct const_operator_head<Return, arg_tuple<Args...>>
{
	virtual Return operator()(Args...) const = 0;
};


}
}
}




#endif /* BOOST_VISITOR_DETAIL_OPERATOR_HEAD_HPP_ */
