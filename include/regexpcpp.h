//
// Created by Bjørn Lindi on 23/04/2020.
//

#ifndef REGEXPCPP_REGEXPCPP_H
#define REGEXPCPP_REGEXPCPP_H

#include <string>

bool validate_card_format(const std::string &s);

const std::string re_show(const std::string &pat, const std::string &s);

#endif //REGEXPCPP_REGEXPCPP_H
