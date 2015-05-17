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
#include <boost/visitor/polymorphic_functor_visitor_adapt.hpp>
#include <boost/visitor/adapt_variant.hpp>

#include <boost/variant/variant.hpp>


#include <iostream>
#include <string>
#include <vector>
#include <sstream>


void run()
{

   using boost::apply_visitor;
   using boost::variant;
   using std::string;
   using std::vector;
   using std::cout;
   using std::endl;
   using std::to_string;
//test the general stuff

   typedef boost::variant<int, double, string> var;
   typedef boost::polynomic_visitor_deduction<void, var> vis;

   double d = 0.;
   int i = 0;
   string s = "";

   auto fv = boost::make_functor_visitor(
			[&](double di){d = di;},
			[&](int ii)	 {i = ii;},
			[&](string si){s = si;}
	   	   );

   auto ad = boost::adapt_polymorphic_visitor<vis>(fv);

   vis &v = ad;

   v(3.2);	BOOST_CHECK(d == 3.2);
   v(42);	BOOST_CHECK(i == 42);
   v("R2D2"); BOOST_CHECK(s == "R2D2");

/*
   auto adc = boost::adapt_polymorphic_visitor<cpoly_vis>(fv);

   cpoly_vis &vc = adc;

   vc(0.);	BOOST_CHECK(d == 0.);
   vc(-1);	BOOST_CHECK(i == -1);
   vc("C3PO"); BOOST_CHECK(s == "C3PO");
*/

   typedef boost::variant<int, double> var_num;


   typedef boost::polynomic_visitor_deduction<double, var_num, var_num> multi_vis;

   auto fv2 = boost::make_functor_visitor(
		   [](int s1, 	 int s2) 	-> double 	{return s1+s2;},
		   [](double s1, int s2) 	 			{return s1-s2;},
		   [](int s1, 	 double s2)  			{return s1/s2;},
		   [](double s1, double s2)  			{return s1*s2;});

   auto ad2 = boost::adapt_polymorphic_visitor<multi_vis>(fv2);

   multi_vis &mv = ad2;

   BOOST_CHECK(mv(40, 2)  == 42.);
   BOOST_CHECK(mv(10., 2) == 8.);
   BOOST_CHECK(mv(40, 2.) == 20.);
   BOOST_CHECK(mv(40., 2.)== 80.);

}



int test_main(int , char* [])
{
   run();
   return 0;
}



#endif /* BIN_DYN_VISITOR_TEST_CPP_ */
