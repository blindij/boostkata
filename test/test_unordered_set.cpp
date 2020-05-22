// File: test_unordered_set.cpp
//
// Using Catch2 to test Boost::unordered_set functionality
#include "catch2/catch.hpp"
#include <boost/unordered_map.hpp>

TEST_CASE("Test a simple unordered map","[unordered_set]"){
   typedef boost::unordered_map<std::string, int> map;
   map x;
   x["one"] = 1;
   x["two"] = 2;
   x["three"] = 3;
   REQUIRE( x.at("one") == 1);
   SECTION("Search for end"){
      REQUIRE(x.find("missing") == x.end());
   }
}
