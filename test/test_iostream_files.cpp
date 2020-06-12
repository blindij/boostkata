// File: test_iostream_files.cpp
//
// Test reading and writing to files with boost.iostream.file_sink and
// boost.iostream.file_source
#include "catch2/catch.hpp"
#include <sstream>                    // for string output stream
#include <boost/filesystem.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <iostreams/example/container_device.hpp>
#include <iostreams/example/unix2dos_filter.hpp>
//#include <iostreams/example/dictionary_filter.hpp>


using namespace std;
namespace io = boost::iostreams;
namespace fs = boost::filesystem;
namespace ex = boost::iostreams::example;

TEST_CASE("Read from gloser.txt","[iostream][fileread]"){
   string ps("gloser.txt");
   string result;
   REQUIRE(fs::exists(ps));
   SECTION("Read from the file"){
      io::stream_buffer<io::file_source> buf(ps);
      istream                            in(&buf);
      getline(in,result);
      REQUIRE( result == "palpable (adj) that is easily noticed by the mind or senses");
   }
}

TEST_CASE("Write to log.txt","[iostream][log]"){
   string ps("log.txt");
   io::stream_buffer<io::file_sink> buf(ps);
   std::ostream out(&buf);
   // out writes to log.txt
   out << "Hello World!\n";
   out.flush();
   REQUIRE(boost::filesystem::file_size(ps) == 13);
   SECTION("Remove log.txt file"){
      REQUIRE(fs::remove(ps));
   }
}

// 
// Use filters in stream output to file
//
TEST_CASE("Use a unix2dos_output_filter to write file","[iostream][unix2dos][invert][file]"){
   string filename("dos.txt");
   io::filtering_ostream out;
   out.push(ex::unix2dos_output_filter());
   out.push(io::file_sink(filename));
   out << "Hello World!\n";  // The length of the string is 13.
   out.flush();              // It increases to 14 with filtering. CR is added
   REQUIRE(boost::filesystem::file_size(filename) == 14);
}

TEST_CASE("Use a inverted unix2dos_input_filter to write file","[iostream][unix2dos][invert][file]"){
   typedef io::inverse<ex::unix2dos_input_filter> unix2dos_output_filter;
   string filename("dos.txt");
   io::filtering_ostream out;
   out.push(invert(ex::unix2dos_input_filter()));
   out.push(io::file_sink(filename));
   out << "Hello World!\n";  // The length of the string is 13.
   out.flush();              // It increases to 14 with filtering. CR is added
   REQUIRE(boost::filesystem::file_size(filename) == 14);
}
