// File: test_iostream_shell_comment.cpp
//
// Here we test use of Boost.iostream filter. The filter removes shell-style
// comments.
#include "catch2/catch.hpp"
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/filesystem.hpp>
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
   string result;
   string ps("shell_comment.md");
   REQUIRE(fs::exists(ps));
   SECTION("Read a line from shell commented file"){
      io::filtering_istream in;
      in.push(ex::shell_comments_input_filter());
      in.push(io::file_source(ps));
      in >> result;
      REQUIRE(result == "Test");
      SECTION("Read rest of the lines from shell commented file"){
         string tmp;
         while( in  >> tmp ){
           result += tmp;
         }
         REQUIRE( result == "TestThereisalwaysThetextusuallyrunsover");
      }
   }
}

TEST_CASE("Use get() with filter to remove shell-style comments","[iostream][get]"){
   char ch;
   string result;
   string ps("shell_comment.md");
   REQUIRE(fs::exists(ps));
   SECTION("Read a line from shell commented file"){
      io::filtering_istream in;
      in.push(ex::shell_comments_input_filter());
      in.push(io::file_source(ps));
      ch = in.get();
      while(  ch != '\n'){
         result += ch;
         ch = in.get();
      }
      REQUIRE( result == "Test");
   }
}

TEST_CASE("Use getline() with filter to remoe shell-style comments","[iostream][getline]"){
   char ch;
   string result,newline;
   string ps("shell_comment.md");
   REQUIRE(fs::exists(ps));
   SECTION("Read a line from shell commented file"){
      io::filtering_istream in;
      in.push(ex::shell_comments_input_filter());
      in.push(io::file_source(ps));
      getline(in, newline);
      result += newline;
      REQUIRE( result == "Test");
      SECTION("Read the file using getline()"){
         while( getline(in,newline)){result += newline;}
         REQUIRE( result == "TestThere is always The text usually runs over" );
      }
   }
}
