// File: test_phoenix_basic.cpp
//
// Examples from the boost::phoenix introduction
//
#include "catch2/catch.hpp"
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/statement.hpp>
#include <boost/phoenix/function.hpp>
#include <algorithm>
#include <sstream>
#include <vector>
//
// ----- add start of new test modules; testing Boost::phoenix
//
using boost::phoenix::if_;
using boost::phoenix::arg_names::arg1;
using boost::phoenix::arg_names::arg2;
using boost::phoenix::val;
using boost::phoenix::ref;
using boost::phoenix::function;

// --- lazy function ---
struct is_odd_ {
   typedef bool result_type;

   template <typename Arg>
   bool operator()(Arg arg1) const {
      return arg1 % 2 == 1;
   }
};

function<is_odd_> is_odd;

// --- lazy operators ---
// ref(x) = 123   // lazy
// x      = 123   // immediate
//
// ref(x)[0]      // lazy
// x[0]           // immediate
//
// ref(x)[ref(i)] // lazy
// ref(x)[i]      // lazy
// x[ref[i]       // illegal (x is not a phoenix primitive or expression)
// ref(x[ref(i)]) // illegal (x is not a phoenix primitive or expression)
TEST_CASE("Lazy function","[lazy][function]"){
   int init[] = { 2, 10, 4, 5, 1, 6, 8, 3, 9, 7 };
   std::vector<int> c(init, init+10);
   typedef std::vector<int>::iterator iterator;

   // Use the lazy function to find the first odd unmber in container c
   iterator it = std::find_if(c.begin(), c.end(), is_odd(arg1));
   REQUIRE( it != c.end());
   SECTION("Verify first odd number"){
      REQUIRE( *it == 5);
   }
}

TEST_CASE("Lazy Statements","[lazy][statements]"){
   std::ostringstream strout;
   int init[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
   std::vector<int> v(init, init+10);
   std::vector<int> x;

   std::for_each(v.begin(), v.end(), if_(arg1 > 5) [ strout << arg1 << ", " ]);

   REQUIRE(strout.str() == "6, 7, 8, 9, 10, ");
}

TEST_CASE("Lazy operators","[lazy]"){
   int init[] { 2, 10, 4, 5, 1, 6, 8, 3, 9, 7 };
   std::vector<int> c(init, init + 10);
   typedef std::vector<int>::iterator iterator;

   // Find the first odd number in container c
   iterator it = std::find_if(c.begin(), c.end(), arg1 % 2 == 1);
   REQUIRE (it != c.end());
   SECTION("Check for odd number"){
      REQUIRE( *it == 5);
   }
}

// ----- arguments -----
TEST_CASE("Test Boost::phoenix arguments","[argument]"){
   int i = 3;
   char const* s = "Hello World!";
   REQUIRE( arg2(i,s) == "Hello World!");
}

// ----- reference -----
TEST_CASE("References are functions.","[ref][int]"){
   int i = 3;
   REQUIRE( ref(i)() == 3);
}

TEST_CASE("Refeferences are functions. Here with a const char.","[ref][char]"){
   char const* s = "Hello World!";
   REQUIRE( ref(s)() == "Hello World!");
}

//
// ----- value ------
//
TEST_CASE("Test Boost::phoenix val() string","[val][string]"){
   std:: string str("Hello, World");
   
   REQUIRE( str == val("Hello, World")());
}

TEST_CASE("Test Boost::phoenix val() integer","[val] [int]"){
   REQUIRE(  val(3)() == 3);
}



