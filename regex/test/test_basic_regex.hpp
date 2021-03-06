//
// Created by Bjørn Lindi on 28/04/2020.
//

#ifndef REGEXPCPP_TEST_BASIC_REGEXP_HPP
#define REGEXPCPP_TEST_BASIC_REGEXP_HPP

#include <string>
#include <boost/tuple/tuple_comparison.hpp>

std::string marys_story("Mary had a little lamb.\n"
                        "And everywhere that Mary\n"
                        "went the lamb was sure\n"
                        "to go.\n");

TEST_CASE("Using quantifiers", "[quantifier]") {
std::string s4("Match with zero in the middle: @@\n"
               "Subexpression occurs, but...:@=!=ABC@\n"
               "Lots of occurences: @=!==!==!==!==!=@\n"
               "Must repeat entire pattern: @=!==!=!==!=@");
std::string s4_match("Match with zero in the middle: {@@}\n"
                     "Subexpression occurs, but...:@=!=ABC@\n"
                     "Lots of occurences: {@=!==!==!==!==!=@}\n"
                     "Must repeat entire pattern: @=!==!=!==!=@");
REQUIRE(re_show("@(=!=)*@", s4) == s4_match);
}

TEST_CASE("Defining scope", "[scope][one]") {
std::string s3("=first first= # =second second= # =first= # =second=");
REQUIRE(re_show("=first|second=", s3) == "{=first} first= # =second {second=} # {=first}= # ={second=}");
}

TEST_CASE("One of the animals", "[or]") {
std::string s2("The pet store sold cats, dogs, and birds");
REQUIRE(re_show("cat|dog|bird", s2) == "The pet store sold {cat}s, {dog}s, and {bird}s");
}

TEST_CASE("Search for character not in range", "[not][a-z]") {
std::string marys_modified_story("{Ma}ry had{ a} little lamb.\n"
                                 "And everywhere that {Ma}ry\n"
                                 "went the lamb was sure\n"
                                 "to go.\n");
REQUIRE(re_show("[^a-z]a", marys_story) == marys_modified_story);
}

TEST_CASE("Use character range", "[a-z}") {
std::string marys_modified_story("Mary {ha}d a little {la}mb.\n"
                                 "And everywhere t{ha}t Mary\n"
                                 "went the {la}mb {wa}s sure\n"
                                 "to go.\n");
REQUIRE(re_show("[a-z]a", marys_story) == marys_modified_story);
}

TEST_CASE("Use groups", "[groups]") {
std::string marys_modified_story("{Mary had} a little lamb.\n"
                                 "And everywhere that Mary\n"
                                 "went the lamb was sure\n"
                                 "to go.\n");
REQUIRE(re_show("(Mary)( )(had)", marys_story) == marys_modified_story);
}

TEST_CASE("Use period in regex", "[period]") {
std::string marys_modified_story("{Ma}ry {ha}d{ a} little {la}mb.\n"
                                 "And everywhere t{ha}t {Ma}ry\n"
                                 "went the {la}mb {wa}s sure\n"
                                 "to go.\n");
REQUIRE(re_show(".a", marys_story) == marys_modified_story);
}

TEST_CASE("Mary at at end of sentence", "[latMary]") {
std::string marys_modified_story("Mary had a little lamb.\n"
                                 "And everywhere that {Mary}\n"
                                 "went the lamb was sure\n"
                                 "to go.\n");
REQUIRE(re_show("Mary$", marys_story) == marys_modified_story);
}

TEST_CASE("Mary at start of sentence", "[firstMary]") {
std::string marys_modified_story("{Mary} had a little lamb.\n"
                                 "And everywhere that Mary\n"
                                 "went the lamb was sure\n"
                                 "to go.\n");
REQUIRE(re_show("^Mary", marys_story) == marys_modified_story);
}

TEST_CASE("Regex escaped pattern", "[regesc]") {
std::string escaped("Regex \\ escaped \\ pattern.");                // The compiler consumes one backslash
std::string modified_escaped("Regex {\\} escaped {\\} pattern."); // Need to add one extra for \/RR
REQUIRE(re_show("(\\\\)", escaped) == modified_escaped);              // to be part of the strings.
}

TEST_CASE("special character escaped", "[bslash]") {
std::string special("Special characters must be escaped.*");
std::string modified("Special characters must be escaped{.*}");
REQUIRE(re_show("(\\.\\*)", special) == modified);
}

TEST_CASE("special character", "[nobslash]") {
std::string special("Special characters must be escaped.*");
std::string modified("{Special characters must be escaped.*}{}");
REQUIRE(re_show("(.*)", special) == modified);
}

TEST_CASE("testmaryslamb{mary}", "[mary]") {
std::string marys_story_modified("{Mary} had a little lamb.\n"
                                 "And everywhere that {Mary}\n"
                                 "went the lamb was sure\n"
                                 "to go.\n");
REQUIRE(re_show("(Mary)", marys_story) == marys_story_modified);
}

TEST_CASE("testmaryslamb", "[a+]") {
std::string marys_modified_story("M{a}ry h{a}d {a} little l{a}mb.\n"
                                 "And everywhere th{a}t M{a}ry\n"
                                 "went the l{a}mb w{a}s sure\n"
                                 "to go.\n");
REQUIRE(re_show("(a+)", marys_story) == marys_modified_story);
}

TEST_CASE("returning a tuple","[tuple]"){
   std::string result("20200716T0207:63");
   boost::tuple<std::string, std::string> result_tuple("20200716T0207","63");
   // boost::tuple<std::string, std::string> result_tuple("test1","test2");
   REQUIRE( result_tuple == re_pair("(\\d{8}T\\d{4}):(\\d{2})", result));
}
#endif //REGEXPCPP_TEST_BASIC_REGEXP_HPP
