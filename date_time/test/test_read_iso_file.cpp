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
      std::ostringstream outstr;
      std::vector<boost::tuple<string,string>> vector_of_timepoints_height_pair;
      std::string pattern("(\\d{8}T\\d{4}):(\\d{2})");
      all_timepoints.pop_back();
      vector<string>::iterator pr;
      for(pr = all_timepoints.begin(); pr != all_timepoints.end(); pr++) {
         vector_of_timepoints_height_pair.push_back(re_pair(pattern, *pr));
      }
      for(auto i=0;i < 3; i++){
         outstr << vector_of_timepoints_height_pair[i].get<0>() << " " << vector_of_timepoints_height_pair[i].get<1>() << std::endl;
      }
      REQUIRE( outstr.str() == "20200716T0206 63\n20200716T0830 33\n20200716T1441 60\n" );
      SECTION("Transform tuple to new tuple with minutes and int"){
         std::vector<boost::tuple<boost::posix_time::ptime, int>> result;
         std::transform(vector_of_timepoints_height_pair.begin(),
                        vector_of_timepoints_height_pair.end(),
                        std::back_inserter(result), 
                        string2datetime_height);
         outstr.str("");
         for(auto i = 0; i < 3; i++){
            outstr << result[i] << "\n";
         }
         REQUIRE( outstr.str() == "(2020-Jul-16 02:06:00 63)\n(2020-Jul-16 08:30:00 33)\n(2020-Jul-16 14:41:00 60)\n" );
      }
   }
}

TEST_CASE("Write all entries to a new txt file","[date_time],[write_to_file]"){
   string file("farsundiso.txt");
   size_t entries_written = 0;
   vector<boost::tuple<boost::posix_time::ptime,int>> entry_vector; //vectorofentries(make_tuple(boost::posix_time::from_iso_string("20200715T0016"),35));
   entry_vector.push_back(boost::make_tuple(boost::posix_time::from_iso_string("20200715T0016"),35));
   entry_vector.push_back(boost::make_tuple(boost::posix_time::from_iso_string("20200715T0645"),20));
   entries_written = write_iso_file(file, entry_vector);
   REQUIRE( entries_written == 2);
}
