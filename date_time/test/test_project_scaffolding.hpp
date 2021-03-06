// file: project_test_scaffolding.hpp
//
// File with simpler test to verify concepts not easily understood
// when using the Boost library
#ifndef TEST_PROJECT_SCAFFOLDING_HPP
#define TEST_PROJECT_SCAFFOLDING_HPP
#include "ebb_flow.h"
#include <sstream>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

TEST_CASE("Convert string to int","[date_time],[atoi]"){
   istringstream h("63");
   int f;
   h >> f;
   REQUIRE( f == 63);
}

TEST_CASE("Construct time object from ISO string","[date_time][isostring]"){
   ptime t1(date(2020,Jul,16),hours(2)+minutes(6));
   std::string  ts("20200716T0206");
   ptime t2(from_iso_string(ts));

   REQUIRE( t1 == t2 );
   SECTION("Subtract 25 minutes"){
      // Mandal subtract 15 minutes, Farsun 20 minutes
      // => Estimate 25 minutes for Hidra
      ptime t3(date(2020,Jul,16), hours(1)+minutes(41));
      REQUIRE ( t3 == (t2 - minutes(25)) );
   }
}

TEST_CASE("Construct time object just after midnight","[date_time],[midnight]"){
   ptime t1(date(2020,Jul,8), minutes(16));
   std::string ts("20200708T0016");
   ptime t2(from_iso_string(ts));
   REQUIRE( t1 == t2);
   SECTION("Subtract 25 minutes"){
      ptime t3(date(2020,Jul,7), hours(23)+minutes(51));
      REQUIRE ( t3 == (t2 + minutes(-25)) );
      SECTION("Output simple string"){
         REQUIRE( to_simple_string(t3) == "2020-Jul-07 23:51:00");
      }
   }
}
#endif // end TEST_PROJECT_SCAFFOLDING_HPP
