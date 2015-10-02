//  Boost.Visitor
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).


#ifndef BOOST_VISITOR_DETAIL_POLY_FROM_VARIANT_HPP_
#define BOOST_VISITOR_DETAIL_POLY_FROM_VARIANT_HPP_

#include <boost/visitor/polymorphic_visitor.hpp>
#include <boost/visitor/arg_tuple.hpp>
#include <boost/config/select_compiler_config.hpp>
#include <boost/config/suffix.hpp>
#include <boost/variant.hpp>

namespace boost
{

namespace detail {
namespace visitor {


template<typename T>
struct deduce_for_poly { };

template<typename ...Args>
struct deduce_for_poly<boost::variant<Args...>>
{
	using type = arg_tuple<arg_tuple<Args>...>;
};


template<typename Var, typename Arg> struct append {};
template<typename ... Vars, typename Arg>
struct append<arg_tuple<Vars...>, Arg>
{
	using type = arg_tuple<Vars..., Arg>;
};

template<typename Var, typename Arg> struct append_tuple {};
template<typename ... Vars, typename ...Args>
struct append_tuple<arg_tuple<Vars...>, arg_tuple<Args...>>
{
	using type = arg_tuple<Vars..., Args...>;
};


template<typename ArgTuple, typename Arg>
struct append_each {};

template<typename Current, typename ...Args, typename Arg>
struct append_each<arg_tuple<Current, Args...>, Arg>
{
	using my_type = arg_tuple<BOOST_DEDUCED_TYPENAME append<Current, Arg>::type>;
	using next = BOOST_DEDUCED_TYPENAME append_each<arg_tuple<Args...>, Arg>::type;
	using type = BOOST_DEDUCED_TYPENAME append_tuple<my_type, next>::type;
};

template<typename Current, typename Arg>
struct append_each<arg_tuple<Current>, Arg>
{
	using type = arg_tuple<BOOST_DEDUCED_TYPENAME append<Current, Arg>::type>;
};


template<typename VarTuple, typename T>
struct combine_step
{
	using type = BOOST_DEDUCED_TYPENAME append<VarTuple, T>::type; //append for this one.

};

template<typename ... Vars, typename T>
struct combine_step<arg_tuple<Vars...>, T>
{
	using type = arg_tuple<BOOST_DEDUCED_TYPENAME append<Vars, T>::type...>;
};

//first is the current tuple, second are the arguments to be appended.
template<typename VarTuple, typename ...Args>
struct combine_loop{};

//VarTuple arg_tuple<arg_tuple<Args>>, second T,
template<typename VarTuple, typename Current, typename ...Args>
struct combine_loop<VarTuple, Current, Args...>
{
	using my_type = BOOST_DEDUCED_TYPENAME append_each<VarTuple, Current>::type;
	using next = BOOST_DEDUCED_TYPENAME combine_loop<VarTuple, Args...>::type;

	using type = BOOST_DEDUCED_TYPENAME append_tuple<my_type, next>::type;
};

template<typename VarTuple,typename Current>
struct combine_loop<VarTuple, Current>
{
	using type = BOOST_DEDUCED_TYPENAME append_each<VarTuple, Current>::type;
};




template<typename ...> struct combine;
//first is an arg_tuple of arg_tuples, second are variants.
template<typename VarTuple, typename ...Args>
struct combine<VarTuple, boost::variant<Args...>>
{
	using type = BOOST_DEDUCED_TYPENAME combine_loop<VarTuple, Args...>::type;
};

template<typename Variable, typename ...Args>
struct multi_deduce_for_poly { };

//variable is the current arg_tuple, Last are variants which need to be comined with it, args is the rest.
template<typename Variable, typename Current, typename ...Args>
struct multi_deduce_for_poly<Variable, Current, Args...>
{
	using current_var = BOOST_DEDUCED_TYPENAME combine<Variable, Current>::type;
	using type = BOOST_DEDUCED_TYPENAME multi_deduce_for_poly<current_var, Args...>::type;
};


//variable is the current arg_tuple, Last are variants which need to be comined with it
template<typename Variable, typename Last>
struct multi_deduce_for_poly<Variable, Last>
{
	using type = BOOST_DEDUCED_TYPENAME combine<Variable, Last>::type;
};

//First is an arg_tuple, second are more arg_tuples, which need to be combined
template<typename First, typename ... Args>
struct multi_deduce_for_poly_start
{
	using type = BOOST_DEDUCED_TYPENAME multi_deduce_for_poly<BOOST_DEDUCED_TYPENAME deduce_for_poly<First>::type, Args...>::type;
};


template<typename Return, typename T>
struct single_deduce_for_poly { };

template<typename Return, typename ...Args>
struct single_deduce_for_poly<Return, boost::variant<Args...>>
{
	using type = polymorphic_visitor<Return, Args...>;
};


template<typename Return, typename ArgTuple>
struct poly_from_variant_expand {};

template<typename Return, typename ...Args>
struct poly_from_variant_expand<Return, arg_tuple<Args...>>
{
	using type = polymorphic_visitor<Return, Args...>;
};

template<typename Return, typename... Variants>
struct poly_from_variant_t
{
	using arg_tuple = BOOST_DEDUCED_TYPENAME multi_deduce_for_poly_start<Variants...>::type;
	using type = BOOST_DEDUCED_TYPENAME poly_from_variant_expand<Return, arg_tuple>::type;
};

template<typename Return, typename Variant>
struct poly_from_variant_t<Return, Variant>
{
	using type = BOOST_DEDUCED_TYPENAME single_deduce_for_poly<Return, Variant>::type;
};



template<typename Return, typename ... Variants>
using poly_from_variant = BOOST_DEDUCED_TYPENAME poly_from_variant_t<Return, Variants...>::type;

}}

template<typename Return, typename ...Variants>
using polynomic_visitor_deduction = detail::visitor::poly_from_variant<Return, Variants...>;


}



#endif /* BOOST_VISITOR_DETAIL_POLY_FROM_VARIANT_HPP_ */
