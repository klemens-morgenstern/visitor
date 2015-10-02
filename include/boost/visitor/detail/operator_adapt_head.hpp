//  Boost.Variant
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).


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
	operator_adapt_head(Visitor & vis) : Next(vis) {}
	virtual BOOST_DEDUCED_TYPENAME Visitor::result_type operator()(T arg) override
	{
		return this->vis(arg);
	};
};

template<typename Visitor, typename Next, typename ...Args>
struct operator_adapt_head<Visitor, Next, arg_tuple<Args...>> : Next
{
	operator_adapt_head(const operator_adapt_head&) = default;
	operator_adapt_head(Visitor & vis) : Next(vis){}
	virtual BOOST_DEDUCED_TYPENAME Visitor::result_type operator()(Args... args) override
	{
		return this->vis(args...);
	}
};

template<typename Visitor, typename Next, typename T>
struct const_operator_adapt_head : Next
{
	const_operator_adapt_head(const const_operator_adapt_head&) = default;
	const_operator_adapt_head(Visitor & vis) : Next(vis) {}
	virtual BOOST_DEDUCED_TYPENAME Visitor::result_type operator()(T arg) const override
	{
		return this->vis(arg);
	}
};

template<typename Visitor, typename Next, typename ...Args>
struct const_operator_adapt_head<Visitor, Next, arg_tuple<Args...>> : Next
{
	const_operator_adapt_head(const const_operator_adapt_head&) = default;
	const_operator_adapt_head(Visitor & vis) : Next(vis) {}
	virtual BOOST_DEDUCED_TYPENAME Visitor::result_type operator()(Args... args) const override
	{
		return this->vis(args...);
	}
};


}
}
}




#endif /* BOOST_VISITOR_DETAIL_OPERATOR_HEAD_HPP_ */
