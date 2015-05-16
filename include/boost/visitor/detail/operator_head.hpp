/*
 * get_operator.hpp
 *
 *  Created on: 06.05.2015
 *      Author: Klemens
 */

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
	virtual ~operator_head() = default;
};

template<typename Return, typename ...Args>
struct operator_head<Return, arg_tuple<Args...>>
{
	virtual Return operator()(Args...) = 0;
	virtual ~operator_head()  = default;
};

template<typename Return, typename T>
struct const_operator_head
{
	virtual Return operator()(T) const = 0;
	virtual ~const_operator_head() = default;
};

template<typename Return, typename ...Args>
struct const_operator_head<Return, arg_tuple<Args...>>
{
	virtual Return operator()(Args...) const = 0;
	virtual ~const_operator_head()  = default;
};


}
}
}




#endif /* BOOST_VISITOR_DETAIL_OPERATOR_HEAD_HPP_ */
