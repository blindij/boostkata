#include "catch2/catch.hpp"
#include <boost/filesystem.hpp>
#include <boost/iostreams/operations.hpp>             // put
#include "iostreams/example/container_device.hpp"



using namespace std;
namespace io = boost::iostreams;
namespace ex = boost::iostreams::example;

TEST_CASE("Testing iostreams::put","[iostreams][put]"){
   typedef ex::container_sink<string> string_sink;
   string result;
   io::stream<string_sink> out(result);
   REQUIRE(io::put(out,'H'));
   SECTION("Testing result"){
      out.flush();
      REQUIRE(result == "H");
   }
}

TEST_CASE("Using a container device","[iostreams][device]"){
   typedef ex::container_device<string> string_device;
   string one, two;
   io::stream<string_device> io(one);
   io << "Hello World!!!";
   io.flush();
   io.seekg(0, BOOST_IOS::beg); // seek to the beginning
   getline(io, two);
   REQUIRE( one == two);
}

TEST_CASE("Write to container_source","[iostreams][write]"){
   typedef ex::container_sink<string> string_sink;
   string result;
   io::stream<string_sink> out(result);
   out << "Hello_world again!";
   out.flush();
   REQUIRE(result == "Hello_world again!");
}

TEST_CASE("Read from a container_source","[iostreams][read]"){
   typedef ex::container_source<std::string> string_source;
   std::string                     input = "Hello World!";
   std::string                     output;
   io::stream<string_source>  in(input);
   getline(in, output);
   REQUIRE( input == output);
}

