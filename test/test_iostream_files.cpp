#include "catch2/catch.hpp"
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <iostream>
#include <boost/iostreams/stream.hpp>
#include <boost/filesystem.hpp>
#include <iostreams/example/container_device.hpp>
#include "iostreams/example/shell_comments_filter.hpp"


using namespace std;
namespace io = boost::iostreams;
namespace fs = boost::filesystem;
namespace ex = boost::iostreams::example;

TEST_CASE("Write line with a comment to file, removing the comment","[iostream][write_no_comment"){
   string ps("nocomment.txt");
   io::filtering_ostream out;
   out.push(ex::shell_comments_output_filter());
   out.push(io::file_sink(ps));
   out << "This is a test with comment. # This text should be removed.\n";
   out.flush();
   REQUIRE(boost::filesystem::file_size(ps) == 30);
}

TEST_CASE("Test for existence of shell commented file","[iostream][shell_comment]"){
   typedef ex::container_source<string> string_source;
   string result;
   string ps("shell_comment.md");
   REQUIRE(fs::exists(ps));
   SECTION("Read a line from shell commented file"){
      io::stream_buffer<io::file_source> buf(ps);
      istream                           in(&buf);
      getline(in,result);
      REQUIRE(result == "# Title in a Markdown file");
//      SECTION("Remove shell comments"){
//         string output;
//         io::filtering_istream in;
//         REQUIRE( in.push(ex::shell_comments_input_filter(result)) == EOF);
//      }
   }
}

TEST_CASE("Read from gloser.txt","[iostream][fileread]"){
   // io::filtering_istream in;
   //
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


