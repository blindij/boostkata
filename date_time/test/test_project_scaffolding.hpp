// file: project_test_scaffolding.hpp
//
// File with simpler test to verify concepts not easily understood
// when using the Boost library
#ifndef TEST_PROJECT_SCAFFOLDING_HPP
#define TEST_PROJECT_SCAFFOLDING_HPP
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;

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
      REQUIRE ( t3 == (t2 - minutes(25)) );
   }
}

#endif // end TEST_PROJECT_SCAFFOLDING_HPP
