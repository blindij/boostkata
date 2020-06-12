// File: test_iostream_unix2dos.cpp
//
//  Test the unix2dos output filter. Are we adding a CR?

#include "catch2/catch.hpp"
#include "iostreams/example/container_device.hpp"
#include "iostreams/example/unix2dos_filter.hpp"
#include <boost/iostreams/invert.hpp>              //?
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

using namespace std;
namespace io = boost::iostreams;
namespace ex = boost::iostreams::example;

TEST_CASE("Use unix2dos output_filter","[iostream][unix2dos]"){
   typedef ex::container_sink<string> string_sink;
   string result;
   io::filtering_ostream out; 
   out.push(ex::unix2dos_output_filter());
   out.push(back_inserter(result));
   out << "Hello World!\n";  // The length of the s tring is 13 characters
   out.flush();
   REQUIRE( result == "Hello World!\r\n");
   SECTION("Check that the length of the string is 14 characters"){
      REQUIRE( result.length() == 14);
   }
}
