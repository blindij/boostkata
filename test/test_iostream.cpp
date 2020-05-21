#include "catch2/catch.hpp"
#include "iostreams/example/container_device.hpp"

using namespace std;
namespace io = boost::iostreams;
namespace ex = boost::iostreams::example;

TEST_CASE("Write to container_source","[iostream][write]"){
   typedef ex::container_sink<string> string_sink;
   string result;
   io::stream<string_sink> out(result);
   out << "Hello_world again!";
   out.flush();
   REQUIRE(result == "Hello_world again!");
}

TEST_CASE("Read from a container_source","[iostream][read]"){
   typedef ex::container_source<std::string> string_source;
   std::string                     input = "Hello World!";
   std::string                     output;
   io::stream<string_source>  in(input);
   getline(in, output);
   REQUIRE( input == output);
}

TEST_CASE("Write to log.txt","[iostream][log]"){
   io::stream_buffer<io::file_sink> buf("log.txt");
   std::ostream out(&buf);
   // out writes to log.txt
   out << "Hello World!\n";
}
