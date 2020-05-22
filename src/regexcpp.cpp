//
// Created by Bjørn Lindi on 23/04/2020.
//
#include "regexpcpp.h"
#include <boost/regex.hpp>

bool validate_card_format(const std::string &s) {
    static const boost::regex e("(\\d{4}[- ]){3}\\d{4}");
    return regex_match(s, e);
}

const std::string re_show(const std::string &pat, const std::string &s) {
    boost::regex reg(pat, boost::regex::perl);
    return boost::regex_replace(s, reg, "{$0}");
}
