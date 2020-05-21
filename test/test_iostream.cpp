#include "catch2/catch.hpp"
#include "iostreams/example/container_device.hpp"


TEST_CASE("Read from a container_source","[iostream][read]"){
   namespace io = boost::iostreams;
   namespace ex = boost::iostreams::example;
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
