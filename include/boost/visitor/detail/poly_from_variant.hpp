/*
 * poly_from_variant.hpp
 *
 *  Created on: 06.05.2015
 *      Author: Klemens
 */

#ifndef BOOST_VISITOR_DETAIL_POLY_FROM_VARIANT_HPP_
#define BOOST_VISITOR_DETAIL_POLY_FROM_VARIANT_HPP_

#include <boost/visitor/polymorphic_visitor.hpp>
#include <boost/visitor/arg_tuple.hpp>
#include <boost/config/select_compiler_config.hpp>
#include <boost/config/suffix.hpp>

namespace boost
{

template<typename ...Args>
class variant;

namespace detail {
namespace visitor {


template<typename T>
struct deduce_for_poly { };

template<typename ...Args>
struct deduce_for_poly<variant<Args...>>
{
	using type = arg_tuple<arg_tuple<Args...>>;
};

template<typename Var, typename Arg> struct append {};
template<typename ... Vars, typename Arg>
struct append<arg_tuple<Vars...>, Arg>
{
	using type = arg_tuple<Vars..., Arg>;
};

template<typename ... Vars, typename ...Args>
struct append<arg_tuple<Vars...>, arg_tuple<Args...>>
{
	using type = arg_tuple<Vars..., Args...>;
};

template<typename Variable, typename ...Args>
struct combine_step {};

template<typename Var, typename T, typename ...Args>
struct combine_step<Var, T, Args...>
{
	using my_type = BOOST_DEDUCED_TYPENAME append<Var, T>::type; //append for this one.
	using next_type = BOOST_DEDUCED_TYPENAME combine_step<Var, Args...>::type;
	using type = BOOST_DEDUCED_TYPENAME append<my_type, next_type>::type;
};

template<typename Var, typename T>
struct combine_step<Var, T>
{
	using type = BOOST_DEDUCED_TYPENAME append<Var, T>::type; //append for this one.
};


template<typename Variable, typename Next> struct combine {};

template<typename Variable, typename ...Args>
struct combine<Variable, arg_tuple<Args...>>
{
	using type = BOOST_DEDUCED_TYPENAME combine_step<Variable, Args...>::type;
};


template<typename Variable, typename ...Args>
struct multi_deduce_for_poly { };

template<typename Variable, typename Current, typename ...Args>
struct multi_deduce_for_poly<Variable, Current, Args...>
{
	using type = BOOST_DEDUCED_TYPENAME multi_deduce_for_poly<BOOST_DEDUCED_TYPENAME combine<Variable, Current>::type, Args...>::type;
};

template<typename Variable, typename Last>
struct multi_deduce_for_poly<Variable, Last>
{
	using type = BOOST_DEDUCED_TYPENAME combine<Variable, Last>::type;
};

template<typename T, typename ... Args>
struct multi_deduce_for_poly_start
{
	using type = BOOST_DEDUCED_TYPENAME multi_deduce_for_poly<BOOST_DEDUCED_TYPENAME deduce_for_poly<T>::type, Args...>::type;
};


template<typename Return, typename T>
struct single_deduce_for_poly { };

template<typename Return, typename ...Args>
struct single_deduce_for_poly<Return, variant<Args...>>
{
	using type = polymorphic_visitor<Return, Args...>;
};



template<typename Return, typename... Variants>
struct poly_from_variant_t
{
	using type = polymorphic_visitor<Return, BOOST_DEDUCED_TYPENAME multi_deduce_for_poly_start<Return, Variants...>::type>;

};

template<typename Return, typename Variant>
struct poly_from_variant_t<Return, Variant>
{
	using type = BOOST_DEDUCED_TYPENAME single_deduce_for_poly<Return, Variant>::type;
};


}}}



#endif /* BOOST_VISITOR_DETAIL_POLY_FROM_VARIANT_HPP_ */
