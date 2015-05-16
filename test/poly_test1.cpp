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

#include <boost/variant/variant.hpp>


#include <iostream>
#include <string>
#include <vector>

enum type_t
{
   int_,
   double_,
   string_
};

void run()
{

   using boost::apply_visitor;
   using boost::variant;
   using std::string;
   using std::vector;
   using std::cout;
   using std::endl;

//test the general stuff

   typedef boost::polymorphic_visitor<type_t, int, double, string> poly_vis;

   struct vis : poly_vis
   {
	   virtual type_t operator()(int i)  override {   return int_;   }
	   virtual type_t operator()(double) override {   return double_;   }
	   virtual type_t operator()(string) override {   return string_;   }
   };

   vis x;

   poly_vis &v = x;
   BOOST_CHECK(v(42) == int_);

   BOOST_CHECK(v(3.142) == double_);
   BOOST_CHECK(v("") == string_);




   typedef boost::const_polymorphic_visitor<type_t, double, int, string> cpoly_vis;

   struct cvis : cpoly_vis
   {
	   virtual type_t operator()(int i)  const override {   return int_;   }
	   virtual type_t operator()(double) const override {   return double_;   }
	   virtual type_t operator()(string) const override {   return string_;   }
   };

   cvis cx;

   cpoly_vis &cv = cx;
   BOOST_CHECK(cv(42) == int_);

   BOOST_CHECK(cv(3.142) == double_);
   BOOST_CHECK(cv("") == string_);


   //now test with a variant
   boost::variant<string, int, double> var = 2.3;

   BOOST_CHECK(var.apply_visitor(v) == double_);
   BOOST_CHECK(var.apply_visitor(cv) == double_);
}



int test_main(int , char* [])
{
   run();
   return 0;
}



#endif /* BIN_DYN_VISITOR_TEST_CPP_ */
