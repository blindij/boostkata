//
// Created by Bjørn Lindi on 23/04/2020.
//
#include "regexpcpp.h"
#include <boost/regex.hpp>
#include <iostream>  // std::cout

bool validate_card_format(const std::string &s) {
    static const boost::regex e("(\\d{4}[- ]){3}\\d{4}");
    return regex_match(s, e);
}

const std::string re_show(const std::string &pat, const std::string &s) {
    boost::regex reg(pat, boost::regex::perl);
    return boost::regex_replace(s, reg, "{$0}");
}

const std::string re_dictword(const std::string &pat, const std::string &s) {
    boost::regex reg(pat, boost::regex::perl);
    return boost::regex_replace(s, reg, "${1}");
}

boost::tuple<std::string, std::string> re_pair(const std::string &pat, const std::string &s){
   boost::regex reg(pat, boost::regex::perl);
   boost::smatch what;
   std::string part_one,part_two;
   if (boost::regex_match(s,what,reg, boost::match_extra)){
      part_one = what[1];
      part_two = what[2];
   } 
   
   return boost::make_tuple(part_one, part_two);
}
