// File: test_iostream_files.cpp
//
// Test reading and writing to files with boost.iostream.file_sink and
// boost.iostream.file_source
#include "catch2/catch.hpp"
#include <sstream>                    // for string output stream
#include <boost/filesystem.hpp>
#include <iostreams/example/container_device.hpp>
#include <iostreams/example/dictionary_filter.hpp>


using namespace std;
namespace io = boost::iostreams;
namespace fs = boost::filesystem;
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
}

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


