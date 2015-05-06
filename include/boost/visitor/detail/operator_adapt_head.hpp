/*
 * get_operator.hpp
 *
 *  Created on: 06.05.2015
 *      Author: Klemens
 */

#ifndef BOOST_VISITOR_DETAIL_OPERATOR_ADAPT_HEAD_HPP_
#define BOOST_VISITOR_DETAIL_OPERATOR_ADAPT_HEAD_HPP_

#include <boost/config/suffix.hpp>
#include <boost/visitor/arg_tuple.hpp>

namespace boost {
namespace detail {
namespace visitor {

template<typename Visitor, typename Next, typename T>
struct operator_adapt_head : Next
{
	operator_adapt_head(const operator_adapt_head&) = default;
	operator_adapt_head(Visitor & vis) : Next(vis), vis(vis) {}
	virtual BOOST_DEDUCED_TYPENAME Visitor::result_type operator()(T arg)
	{
		return vis(arg);
	};
};

template<typename Visitor, typename Next, typename ...Args>
struct operator_adapt_head<Visitor, Next, arg_tuple<Args...>> : Next
{
	operator_adapt_head(const operator_adapt_head&) = default;
	operator_adapt_head(Visitor & vis) : Next(vis), vis(vis) {}
	virtual BOOST_DEDUCED_TYPENAME Visitor::result_type operator()(Args... args)
	{
		return vis(args...);
	}
};

template<typename Visitor, typename Next, typename T>
struct const_operator_adapt_head : Next
{
	const_operator_adapt_head(const const_operator_adapt_head&) = default;
	const_operator_adapt_head(Visitor & vis) : Next(vis), vis(vis) {}
	virtual BOOST_DEDUCED_TYPENAME Visitor::result_type operator()(T arg) const
	{
		return vis(arg);
	}
};

template<typename Visitor, typename Next, typename ...Args>
struct const_operator_adapt_head<Visitor, Next, arg_tuple<Args...>> : Next
{
	const_operator_adapt_head(const const_operator_adapt_head&) = default;
	const_operator_adapt_head(Visitor & vis) : Next(vis), vis(vis) {}
	virtual BOOST_DEDUCED_TYPENAME Visitor::result_type operator()(Args... args) const
	{
		return vis(args...);
	}
};


}
}
}




#endif /* BOOST_VISITOR_DETAIL_OPERATOR_HEAD_HPP_ */
