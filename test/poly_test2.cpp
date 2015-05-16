/*
 * dyn_visitor_test.cpp
 *
 *  Created on: 16.05.2015
 *      Author: Klemens
 */

#ifndef BIN_DYN_VISITOR_TEST_CPP_
#define BIN_DYN_VISITOR_TEST_CPP_



//-----------------------------------------------------------------------------
// boost-libs variant/test/lambda_test1.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2015
// Klemens Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(disable:4244) // conversion from const int to const short
#endif

#include <boost/test/minimal.hpp>
#include <boost/visitor/polymorphic_visitor.hpp>
#include <boost/visitor/arg_tuple.hpp>

#include <boost/variant/variant.hpp>


#include <iostream>
#include <string>
#include <vector>

void run()
{

   using boost::apply_visitor;
   using boost::variant;
   using std::string;
   using std::vector;
   using std::cout;
   using std::endl;

//test the general stuff

   typedef boost::polymorphic_visitor<double, boost::arg_tuple<int, double>, boost::arg_tuple<double, int>, boost::arg_tuple<int, int>, boost::arg_tuple<double, double>> poly_vis;

   struct vis : poly_vis
   {
	   virtual double operator()(int x, int y) 		 override { return x+y;}
	   virtual double operator()(double x, double y) override { return x*y;}
	   virtual double operator()(int x, double y) 	 override { return x-y;}
	   virtual double operator()(double x, int y) 	 override { return x/y;}
   };

   vis x;

   poly_vis &v = x;
   BOOST_CHECK(v(40, 2) == 42.);

   BOOST_CHECK(v(1.5,2.) == 3.);
   BOOST_CHECK(v(50, 8.0) == 42.);
   BOOST_CHECK(v(100., 25) == 4);

   //i maybe need some more tests here...

   variant<int, double> v1{2.5}, v2{4.};

   BOOST_CHECK(apply_visitor(v, v1, v2) == 10.);
}



int test_main(int , char* [])
{
   run();
   return 0;
}



#endif /* BIN_DYN_VISITOR_TEST_CPP_ */
