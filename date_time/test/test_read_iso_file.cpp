// File: test_helgeroa_iso.cpp
//
// Read the file helgeroaiso.txt which contain time points for
// ebb and flow at Helgeroa in a ISO time format
#include "catch2/catch.hpp"
#include "regexpcpp.h"
#include "ebb_flow.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
namespace fs = boost::filesystem;
namespace io = boost::iostreams;

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
      std::vector<boost::tuple<string,string>> vector_of_timepoints_height_pair;
      std::string pattern("(\\d{8}T\\d{4}):(\\d{4})");
      vector<string>::iterator pr;
      for(pr = all_timepoints.begin(); pr != all_timepoints.end(); pr++) {
         vector_of_timepoints_height_pair.push_back(re_pair(pattern, *pr));
      }
      REQUIRE( vector_of_timepoints_height_pair.size() == 21 );
   }
}
