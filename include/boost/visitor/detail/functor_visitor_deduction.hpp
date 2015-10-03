//  Boost.Varaint
//  Lambda Visitor utilities defined here
//
//  See http://www.boost.org for most recent version, including documentation.
//
//  Copyright Klemens Morgenstern, 2015.
//
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_VARIANT_DETAIL_FUNCTOR_VISITOR_DEDUCTION_HPP
#define BOOST_VARIANT_DETAIL_FUNCTOR_VISITOR_DEDUCTION_HPP

#include <boost/type_traits/is_same.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost {
namespace detail { namespace visitor {

//cause i don't wanna include utility; doesn't really make sense, since i already use c++14
template< class T >
constexpr T&& forward( BOOST_DEDUCED_TYPENAME remove_reference<T>::type& t ) noexcept
{
	return static_cast<T&&>(t);
}
template< class T >
constexpr T&& forward( BOOST_DEDUCED_TYPENAME remove_reference<T>::type&& t )noexcept
{
	return static_cast<T&&>(t);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// functor_parameter_deduction deduct the return type and the parameters of the input.
//
//
template<typename lambda>
struct functor_parameter_deduction
{
};
//the ... comes from possible mutli visitors.
template<typename lambda, typename Ret, typename ...Args>
struct functor_parameter_deduction<Ret(lambda::*)(Args...) const>
{
//	typedef Arg0 type0;
	static constexpr size_t arg_cout = sizeof...(Args);
	typedef Ret return_type;
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////
// used for the actual deduction
//
template<typename Lambda>
struct functor_deduct_parameter
{
	//using types		  = typename functor_parameter_deduction<decltype(&Lambda::operator())>::types;
	using return_type = BOOST_DEDUCED_TYPENAME functor_parameter_deduction<decltype(&Lambda::operator())>::return_type;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  declaration of the actual visitor, i.e. this one is partial and gets inherited
//
template<typename ... Args>
class functor_visitor_helper
{
	void operator()();
};

template<typename Lambda>
class functor_visitor_helper<Lambda> : public Lambda
{
	using father = Lambda;
public:
	using return_type = BOOST_DEDUCED_TYPENAME functor_deduct_parameter<Lambda>::return_type;
	using father::operator();

	template<typename L>
	functor_visitor_helper(L &&lambda) : father(forward<L>(lambda)) {};
};

template<typename Lambda, typename ... Args>
class functor_visitor_helper<Lambda, Args...> : public functor_visitor_helper<Args...>, Lambda
{
	using father = Lambda;
public:
	using functor_visitor_helper<Args...>::operator();
	using return_type = BOOST_DEDUCED_TYPENAME functor_deduct_parameter<Lambda>::return_type;
	using father::operator();

	static_assert(boost::is_same<return_type, typename functor_visitor_helper<Args...>::return_type>::value, "return types must have the same type");


	template<typename L, typename ... l_Args>
	functor_visitor_helper(L && lambda, l_Args && ...ls) :
			functor_visitor_helper<Args...>(forward<l_Args>(ls)...), father(forward<L>(lambda)) {};
};

template<typename ...Args>
struct functor_visitor : public functor_visitor_helper<Args...>, public boost::static_visitor<typename functor_visitor_helper<Args...>::return_type>
{
	using return_type = BOOST_DEDUCED_TYPENAME functor_visitor_helper<Args...>::return_type;
	using functor_visitor_helper<Args...>::operator();
	functor_visitor(Args&&...args) : functor_visitor_helper<Args...>(forward<Args>(args)...) {};
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  explicit lambda visitor
//
template<typename ... Args>
class functor_visitor_helper_exp
{
	void operator()();
};



template<typename Lambda>
class functor_visitor_helper_exp<Lambda> : public Lambda
{
	using father = Lambda;
public:
	using father::operator();
	template<typename L>
	functor_visitor_helper_exp(L &&lambda) : father(forward<L>(lambda)) {};
};

template<typename Lambda, typename ... Args>
class functor_visitor_helper_exp<Lambda, Args...> : public functor_visitor_helper_exp<Args...>, public Lambda
{
	using father = Lambda;
public:
	using functor_visitor_helper_exp<Args...>::operator();
	using father::operator();

	template<typename L, typename ... l_Args>
	functor_visitor_helper_exp(L && lambda, l_Args && ...ls) :
		functor_visitor_helper_exp<l_Args...>(forward<l_Args>(ls)...), father(forward<L>(lambda)) {};
};

template<typename ReturnType, typename ...Args>
struct functor_visitor_exp : public functor_visitor_helper_exp<Args...>, public boost::static_visitor<ReturnType>
{
	using return_type = ReturnType;
	using functor_visitor_helper_exp<Args...>::operator();
	functor_visitor_exp(Args&&...args) : functor_visitor_helper_exp<Args...>(forward<Args>(args)...) {};
};

}}}




#endif /* BOOST_VARIANT_DETAIL_functor_VISITOR_DEDUCTION_HPP_ */
