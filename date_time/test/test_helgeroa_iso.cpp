// File: test_helgeroa_iso.cpp
//
// Read the file helgeroaiso.txt which contain time points for
// ebb and flow at Helgeroa in a ISO time format
#include "catch2/catch.hpp"
#include "regexpcpp.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/filesystem.hpp>
#include <boost/tuple/tuple_comparison.hpp>

using namespace std;
namespace fs = boost::filesystem;
namespace io = boost::iostreams;

size_t read_iso_file(std::string& filename,std::vector<std::string>& vecent){
   string result;
   io::stream_buffer<io::file_source> buf(filename);
   istream in(&buf);
   if (fs::exists(filename)){
      while(in){
         getline(in,result);
         vecent.push_back(result);
      }
   }
   return vecent.size();
}

TEST_CASE("Read from helgeroaiso.txt","[date_time][fileread]"){
  string file("helgeroaiso.txt");
  REQUIRE(fs::exists(file));
  SECTION("Read from the file"){
     string result;
     io::stream_buffer<io::file_source> buf(file);
     istream                            in(&buf);
     getline(in,result);
     REQUIRE( result == "20200716T0206:63");
  }
}

TEST_CASE("Read all entries from helgeroaiso.txt", "[date_time][all]"){
   string file("helgeroaiso.txt");
   vector<string> all_timepoints;
   size_t number_of_entries = read_iso_file(file, all_timepoints);
   REQUIRE( number_of_entries == 21);
   SECTION("Output all timepoints"){
      vector<string>::iterator pr;
      for(pr = all_timepoints.begin(); pr != all_timepoints.end(); pr++) {
         std::cout << *pr << '\n';
      }
      REQUIRE( all_timepoints.size() == 21 );
   }
}
