// File: test_iostream_dict.cpp
//
// Test class dictionary methods. The class is used as part of an dictionary
// IO filter
#include "catch2/catch.hpp"
#include <sstream>                    // for string output stream
// #include <boost/filesystem.hpp>
#include <iostreams/example/container_device.hpp>
#include <iostreams/example/dictionary_filter.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/invert.hpp>
#include "iostreams/example/shell_comments_filter.hpp"
#include "iostreams/example/unix2dos_filter.hpp"


using namespace std;
//namespace io = boost::iostreams;
//namespace fs = boost::filesystem;
namespace ex = boost::iostreams::example;
namespace io = boost::iostreams;
typedef io::inverse<ex::unix2dos_input_filter> unix2dos_output_filter;

TEST_CASE("Testing for carriage return","[cr]"){
   string best("teststring\r\n");
   REQUIRE( best == "teststring\r\n");
}

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

TEST_CASE("Create dictionary and use it for input filter","[iostream],[dictionary][input]"){
   // Create dictionary
   ostringstream myout;
   ex::dictionary d;
   d.add("VW","Volkswagen");
   d.add("AAPL","Apple");
   d.add("NKE","Nike");
   d.add("YHOO","Yahoo");
   myout << d;
   REQUIRE( myout.str() == "(aapl: Apple)\n(nke: Nike)\n(vw: Volkswagen)\n(yhoo: Yahoo)\n");
   SECTION("Use dictionary input filter"){
      typedef ex::container_source<std::string> string_source;
      string input("VW sell cars!#It is true");
      string output;
      io::stream<string_source> in(input);
      io::filtering_istream in_str;
      in_str.push(ex::shell_comments_input_filter());
      in_str.push(ex::dictionary_input_filter(d));
      in_str.push(in);
      getline(in_str, output);
      REQUIRE( output == "Volkswagen sell cars!");
   }
}

TEST_CASE("Use unix2dos output_filter","[iostream][unix2dos]"){
   typedef ex::container_sink<string> string_sink;
   string result;
   // io::stream<string_sink> io(result);
   // unix2dos_input_filter if;
   io::filtering_ostream out; // (back_inserter(result)); // io::back_inserter(result));
   //out_str.push(invert(ex::unix2dos_input_filter()));
   out.push(ex::unix2dos_output_filter());
   out.push(back_inserter(result));
   out << "Hello World!\n";  // The length of the s tring is 13 characters
   out.flush();
   REQUIRE( result == "Hello World!\r\n");
   SECTION("Check that the length of the string is 14 characters"){
      REQUIRE( result.length() == 14);
   }
}

TEST_CASE("Use a unix2dos_output_filter to write file","[iostream][unix2dos][invert][file]"){
   string filename("dos.txt");
   io::filtering_ostream out;
   out.push(ex::unix2dos_output_filter());
   out.push(io::file_sink(filename));
   out << "Hello World!\n";  // The length of the string is 13.
   out.flush();              // It increases to 14 with filtering. CR is added
   REQUIRE(boost::filesystem::file_size(filename) == 14);
}

//TEST_CASE("Use a inverted unix2dos_input_filter to write file","[iostream][unix2dos][invert][file]"){
//   string filename("dos.txt");
//   io::filtering_ostream out;
//   out.push(invert(ex::unix2dos_input_filter()));
//   out.push(io::file_sink(filename));
//   out << "Hello World!\n";  // The length of the string is 13.
//   out.flush();              // It increases to 14 with filtering. CR is added
//   REQUIRE(boost::filesystem::file_size(filename) == 14);
//}
