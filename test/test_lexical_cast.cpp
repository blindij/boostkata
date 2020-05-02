#include "catch2/catch.hpp"
#include <algorithm>
#include <iostream>
#include <locale>
#include <cmath>
#include <vector>
#include <iterator>
#include <set>
#include <boost/lexical_cast.hpp>

struct bad_hmean {
   private:
      double v1;
      double v2;
   public:
      bad_hmean(double a = 0, double b = 0) : v1(a), v2(b){}
      void mesg();
};

inline void bad_hmean::mesg(){
   std::cout << "hmean(" << v1 << ", " << v2 << "):"
               << "invalid arguments: a = -b\n";
}

struct bad_gmean {
   public:
      double v1;
      double v2;
      bad_gmean(double a = 0, double b = 0) :v1(a), v2(b){}
      const char * mesg();
};

inline const char * bad_gmean::mesg() {
   return "gmean() arguments shoulb be >= 0\n";
}


template <class ContainerT>
std::vector<long int> container_to_longs(const ContainerT& container) {
   typedef typename ContainerT::value_type value_type;
   std::vector<long int> ret;
   typedef long int (*func_t)(const value_type&);
   func_t f = &boost::lexical_cast<long int, value_type>;
   std::transform(container.begin(), container.end(), std::back_inserter(ret),f);
   return ret;
}

double hmean(double a, double b){
   if (a == -b) {
      throw "bad hmean() arguments: a = -b not allowd";
   }
   return 2.0 * a * b/ (a + b);
}

double gmean(double a, double b) {
   throw bad_gmean(a,b);
   return std::sqrt(a * b);
}

TEST_CASE("testing hmean throwing object","[lexical_cast][hmean][object]"){
   REQUIRE_THROWS_AS(throw bad_gmean(), bad_gmean);
}

TEST_CASE("testing may own throw","[lexical_cast][hmean]"){
   REQUIRE_THROWS( hmean(10, -10));
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
