// File: test_helgeroa_iso.cpp
//
// Read the file helgeroaiso.txt which contain time points for
// ebb and flow at Helgeroa in a ISO time format
#include "catch2/catch.hpp"
#include "ebb_flow.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
namespace pt = boost::posix_time;
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

TEST_CASE("Try to read file, but throw exception","[date_time],[exception]"){
   string file("testfile.txt");
   vector<string> all_timepoints;
   REQUIRE_THROWS( read_iso_file(file, all_timepoints));
}

TEST_CASE("Read all entries from helgeroaiso.txt", "[date_time][all]"){
   string file("helgeroaiso.txt");
   vector<string> all_timepoints;
   size_t number_of_entries = read_iso_file(file, all_timepoints);
   REQUIRE( number_of_entries == 21);
   SECTION("Output all timepoints"){
      std::ostringstream outstr;
      std::vector<boost::tuple<string,string>> vector_of_timepoints_height_pair;
      std::string pat("(\\d{8}T\\d{4}):(\\d{2})");
      all_timepoints.pop_back();
      transform(all_timepoints.begin(), all_timepoints.end(),
                  std::back_inserter(vector_of_timepoints_height_pair),
                  [&pat](auto & x){
                  boost::regex reg(pat, boost::regex::perl);
                  boost::smatch what;
                  std::string part_one,part_two;
                  if (boost::regex_match(x,what,reg, boost::match_extra)){
                     part_one = what[1];
                     part_two = what[2];
                  } 
                  
                  return boost::make_tuple(part_one, part_two);
                  });
      for(auto i=0;i < 3; i++){
         outstr << vector_of_timepoints_height_pair[i] << std::endl;
      }
      REQUIRE( outstr.str() == "(20200716T0206 63)\n(20200716T0830 33)\n(20200716T1441 60)\n" );
      SECTION("Transform tuple to new tuple with minutes and int"){
         std::vector<boost::tuple<pt::ptime, int>> result;
         std::transform(vector_of_timepoints_height_pair.begin(),
                        vector_of_timepoints_height_pair.end(),
                        std::back_inserter(result), 
                        [](auto & x){
                           pt::ptime t1(pt::from_iso_string(get<0>(x)));
                           istringstream height(get<1>(x));
                           int tmp;
                           height >> tmp;
                           return boost::make_tuple(t1, tmp);
                        });
         outstr.str("");
         for(auto i = 0; i < 3; i++){
            outstr << result[i] << "\n";
         }
         REQUIRE( outstr.str() == "(2020-Jul-16 02:06:00 63)\n(2020-Jul-16 08:30:00 33)\n(2020-Jul-16 14:41:00 60)\n" );
         SECTION("Transform tuple to tuple with new time/height pairs"){
            const double heightfactor = 0.56;
            const int distance_delta = 10;
            const pt::minutes adjust_min(-25);
            std::vector<boost::tuple<pt::ptime, int>> transformed;
            std::transform(result.begin(),
                           result.end(),
                           std::back_inserter(transformed),
                           [&heightfactor, &distance_delta, & adjust_min](auto & x){
                                return boost::make_tuple(get<0>(x) + adjust_min,  get<1>(x) * heightfactor + distance_delta);
                              });
            outstr.str("");
            for(auto i = 0; i < 3; i++){
               outstr << transformed[i] << "\n";
            }
            REQUIRE( outstr.str() == "(2020-Jul-16 01:41:00 45)\n(2020-Jul-16 08:05:00 28)\n(2020-Jul-16 14:16:00 43)\n");
         }
      }
   }
}

TEST_CASE("Write all entries to a new txt file","[date_time],[write_to_file]"){
   string file("farsundiso.txt");
   size_t entries_written = 0;
   vector<boost::tuple<pt::ptime,int>> entry_vector; 
   entry_vector.push_back(boost::make_tuple(pt::from_iso_string("20200715T0016"),35));
   entry_vector.push_back(boost::make_tuple(pt::from_iso_string("20200715T0645"),20));
   entries_written = write_iso_file(file, entry_vector);
   REQUIRE( entries_written == 2);
}
