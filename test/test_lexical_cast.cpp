#include "catch2/catch.hpp"
#include <algorithm>
#include <iostream>
#include <locale>
#include <cmath>
#include <vector>
#include <iterator>
#include <set>
#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/variant.hpp>
#include "BoostKata.hpp"


TEST_CASE("Converts value of Boost.Variant","[lexical_cast][longdouble]"){
   boost::variant<char, int, std::string> v1('0'), v2("10.0001"), v3(1);
   const long double sum = to_long_double(v1) + to_long_double(v2) + to_long_double(v3);
   REQUIRE(11 < sum);
   REQUIRE(sum < 11.1);
}

TEST_CASE("Convert sequence into string","[lexical_cast][sequnece]"){
   boost::tuple<char, int, char, int> decim('-', 10, 'e', 5);
   REQUIRE(stringize(decim) == "-10e5");
}

TEST_CASE("User defined type","[leical_cast][user]"){
   negative_number n(1);
   n = boost::lexical_cast<negative_number>("-100");
   REQUIRE(n.value_without_sign() == 100);
}

TEST_CASE("testing exeption thrown when the input is wrong]","[lexcial_cast],[exception],[syntax]"){
   int i;
   REQUIRE_THROWS_AS( i = boost::lexical_cast<int>("This is text"), boost::bad_lexical_cast);

   
}

TEST_CASE("Assert that a short int is not assigned a large value","[lexical_cast],[exception],[bounds]"){
   short s;
   REQUIRE_THROWS( s = boost::lexical_cast<short>("1000000") );
      // on x86 short usually may not store values greater than 32767
      //assert(false); // Must not reach this
}

// 
// ----- Converting numbers to strings -----
//
TEST_CASE(""){
   std::string s = boost::lexical_cast<std::string>(100);
   REQUIRE( s == "100");
}

//
//  ----- Converting strings to numbers ---
//

TEST_CASE("Convert localized number","[lexical_cast],[Norway]"){
   std::locale::global(std::locale("ru_RU.UTF-8"));
   // In Norway coma sing is used as a decimal separator
   // Changed to Russian as in the example. Could be that nb_NO.UTF-8 is not
   // installed.
   float f = boost::lexical_cast<float>("1,0");
   REQUIRE(f < 1.01);
   REQUIRE(f > 0.99);
   }

TEST_CASE("Convert string set","[lexical_cast][set]"){
   std::set<std::string> str_set;
   str_set.insert("1");
   REQUIRE(container_to_longs(str_set).front() == 1);
}

TEST_CASE("Obfuscating people with curly braces is fun!","[lexical_cast][fun]"){
   typedef boost::array<unsigned char, 2> element_t;
   boost::array<element_t, 2> arrays = {{ {{'1', '0' }}, {{'2','0' }} }};
   REQUIRE(container_to_longs(arrays).back() == 20);
}

TEST_CASE("Cast non-zero terminated strings","[lexical_cast][non-zero]"){
   char chars[] = {'1','0','0' };
   int i = boost::lexical_cast<int>(chars, 3);
   REQUIRE( i == 100 );
}

TEST_CASE("Cast string to int","[lecical_cast]"){
   int i = boost::lexical_cast<int>("100");
   REQUIRE(i == 100);
}
