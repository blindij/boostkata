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


std::ostream& operator<<(std::ostream& os, const negative_number& num){
   os << '-' << num.value_without_sign();
   return os;
}

std::istream& operator>>(std::istream& is, negative_number& num) {
   char ch;
   is >> ch;
   if ( ch != '-') {
      throw std::logic_error("negative_number class desgined to store only NEGATIVE values.");
   }
   unsigned short s;
   is >> s;
   num = negative_number(s);
   return is;
}




