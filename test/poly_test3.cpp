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

   typedef boost::polymorphic_visitor<void, double, string, int> poly_vis;
   typedef boost::polymorphic_visitor<void, double, string, int> cpoly_vis;

   double d = 0.;
   int i = 0;
   string s = "";

   auto fv = boost::make_functor_visitor(
			[&](double di){d = di;},
			[&](int ii)	 {i = ii;},
			[&](string si){s = si;}
	   	   );

   auto ad = boost::adapt_polymorphic_visitor<poly_vis>(fv);

   poly_vis &v = ad;

   v(3.2);	BOOST_CHECK(d == 3.2);
   v(42);	BOOST_CHECK(i == 42);
   v("R2D2"); BOOST_CHECK(s == "R2D2");


   auto adc = boost::adapt_polymorphic_visitor<cpoly_vis>(fv);

   cpoly_vis &vc = adc;

   vc(0.);	BOOST_CHECK(d == 0.);
   vc(-1);	BOOST_CHECK(i == -1);
   vc("C3PO"); BOOST_CHECK(s == "C3PO");

}



int test_main(int , char* [])
{
   run();
   return 0;
}



#endif /* BIN_DYN_VISITOR_TEST_CPP_ */
