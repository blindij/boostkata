//
// Created by Bjørn Lindi on 2020-01-31.
//
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <boost/any.hpp>
#include <iostream>
#include <string>
#include <vector>

TEST_CASE("Hello World","[hw]"){
    std::ostringstream myout;
    myout << "Hello World!" << std::endl;
    REQUIRE( myout.str() == "Hello World!\n");
}

TEST_CASE("Boost Any","[bany]"){
    std::ostringstream myout;
    std::vector<boost::any> some_values;
    some_values.push_back(10);
    some_values.push_back(std::string("Wow!"));
    std::string& s = boost::any_cast<std::string&>(some_values.back());
    s += " That is great!\n";
    myout << s;
    REQUIRE( myout.str() == "Wow! That is great!\n" );
}

TEST_CASE("Boost Any, but empty","[empty]"){
    std::vector<boost::any> some_values;
    REQUIRE( some_values.empty());
}

TEST_CASE("Catch Boost Any","[catch]"){
    std::ostringstream myout;
    std::vector<boost::any> some_values;
    const char* c_str = "Hello there!";
    some_values.push_back(c_str);
    REQUIRE_THROWS_AS(boost::any_cast<std::string&>(some_values.back()),boost::bad_any_cast);
}