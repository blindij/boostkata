//
// Created by Bjørn Lindi on 01/05/2020.
//

#ifndef REGEXPCPP_TEST_INTERMEDIATE_REGEXP_HPP
#define REGEXPCPP_TEST_INTERMEDIATE_REGEXP_HPP
#include <catch2/catch.hpp>
#include <string>
#include "regexpcpp.h"

std::string s5("AAAD\n"
               "ABBBBCD\n"
               "BBBCD\n"
               "ABCCD\n"
               "AAABBBC\n");

std::string s6("aaaaa bbbbb ccccc\n"
               "aaa bbb ccc\n"
               "aaaaa bbbbbbbbbbbbbb ccccc\n");

std::string s7("jkl xyz abc\n"
               "jkl xyz xyz\n"
               "jkl abc abc\n");

TEST_CASE("match one or the other","[intermediate][oneortheother]"){
   REQUIRE(re_show("(abc|xyz) (abc|xyz)",s7) == "jkl {xyz abc}\n"
                                                "jkl {xyz xyz}\n"
                                                "jkl {abc abc}\n");
}

TEST_CASE("repeat pattern","[intermediate][repeat]"){
   // remember extra escape \, as compiler takes one
   REQUIRE(re_show("(abc|xyz) \\1",s7) == "jkl xyz abc\n"
                                          "jkl {xyz xyz}\n"
                                          "jkl {abc abc}\n");
}

TEST_CASE("even more counts","[intermediate][count++]"){
   REQUIRE(re_show("a{5} b{6,} c{4,8}", s6) == "aaaaa bbbbb ccccc\n"
                                               "aaa bbb ccc\n"
                                               "{aaaaa bbbbbbbbbbbbbb ccccc}\n");
}

TEST_CASE("more counts","[intermediate],[count+]"){
   REQUIRE(re_show("a+ b{3,} c?",s6) == "{aaaaa bbbbb c}cccc\n"
                                        "{aaa bbb c}cc\n"
                                        "{aaaaa bbbbbbbbbbbbbb c}cccc\n");
}

TEST_CASE("use count","[intermediate][count]"){
   REQUIRE(re_show("a{5} b{0,6} c{4,8}",s6) == "{aaaaa bbbbb ccccc}\n"
                                              "aaa bbb ccc\n"
                                              "aaaaa bbbbbbbbbbbbbb ccccc\n");
}

TEST_CASE("use pluss","[intermediate][pluss]"){
   REQUIRE(re_show("A+B*C?D",s5) == "{AAAD}\n"
                                    "{ABBBBCD}\n"
                                    "BBBCD\n"
                                    "ABCCD\n"
                                    "AAABBBC\n");
}

TEST_CASE("match first word in sentence","[gloser][word]"){
   std::string  result("palpable (adj) that is easily noticed by the mind or senses");
   REQUIRE(re_dictword("([a-z]+)( +.*)", result) == "palpable");
}

TEST_CASE("match the rest of the sentence","[gloser][meaning]"){
   std::string  result("palpable (adj) that is easily noticed by the mind or senses");
   REQUIRE(re_dictword("[a-z]+( +.*)", result) == " (adj) that is easily noticed by the mind or senses");
   
}
#endif  // REGEXPCPP_TEST_INTERMEDIATE_REGEXP_HPP

