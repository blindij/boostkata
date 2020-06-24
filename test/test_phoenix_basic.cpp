// File: test_phoenix_basic.cpp
//
// Examples from the boost::phoenix introduction
//
#include "catch2/catch.hpp"
#include <boost/phoenix/core.hpp>
#include <algorithm>
#include <iostream>
// #include <string>
#include <vector>
//
// ----- add start of new test modules; testing Boost::phoenix
//
using boost::phoenix::arg_names::arg1;
using boost::phoenix::arg_names::arg2;
using boost::phoenix::val;
using boost::phoenix::ref;

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



