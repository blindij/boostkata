// File: test_iostream_dict.cpp
//
// Test class dictionary methods. The class is used as part of an dictionary
// IO filter
#include "catch2/catch.hpp"
#include <sstream>                    // for string output stream
// #include <boost/filesystem.hpp>
// #include <iostreams/example/container_device.hpp>
#include <iostreams/example/dictionary_filter.hpp>


using namespace std;
//namespace io = boost::iostreams;
//namespace fs = boost::filesystem;
namespace ex = boost::iostreams::example;

TEST_CASE("Testing maps and iterators","[map][iterator]"){
   typedef map<string,float> StringFloatMap;
   StringFloatMap stocks;
   stocks["BASF"] = 3.1;
   stocks["VW"] = 2.4;
   ostringstream oss;
   StringFloatMap::iterator pos;
   for (pos = stocks.begin(); pos != stocks.end(); ++pos){
      oss << "(" << pos->first << ": " << pos->second << ")\n";
   }
   REQUIRE( oss.str() == "(BASF: 3.1)\n(VW: 2.4)\n");
   
}

TEST_CASE("Add a key to the dictionary","[iostream][dictionary][add]"){
   ostringstream myout;
   ex::dictionary d;
   d.add("palpable","(adj) that is easily noticed by the mind or senses");
   myout << d;
   REQUIRE( myout.str() == "(palpable: (adj) that is easily noticed by the mind or senses)\n");
   SECTION("Replace"){
      string key("palpable");
      d.replace(key);
      REQUIRE( key == "(adj) that is easily noticed by the mind or senses");
      
   }
}


