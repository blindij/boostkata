#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <boost/phoenix/core.hpp>
// #include <iostream>
// #include <string>
// #include <vector>
//
// ----- add start of new test modules; testing Boost::phoenix
//
using boost::phoenix::val;
using boost::phoenix::ref;

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


