//
// Created by Bjørn Lindi on 2020-01-31.
//
#include "catch2/catch.hpp"
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <string>
#include <vector>


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

TEST_CASE("Get value form boost::any, second approach","[second]"){
    std::ostringstream myout;
    boost::any variable(std::string("Hello world!"));
    std::string* s2 = boost::any_cast<std::string>(&variable);
    myout << *s2;
    REQUIRE( myout.str() == "Hello world!" );
}

// -----------------------------------------------------------
// Testing Boost::variant
// -----------------------------------------------------------

typedef boost::variant<int, const char*, std::string> the_var_t;

TEST_CASE("Unrestricted unions using Boost.Variant","[union]"){
    std::ostringstream myout;
    std::vector<the_var_t> some_values;
    some_values.push_back(10);
    some_values.push_back("Hello there!");
    some_values.push_back(std::string("Wow!"));
    std::string& s = boost::get<std::string>(some_values.back());
    s += " That is great!\n";
    myout << s;
    REQUIRE( myout.str() == "Wow! That is great!\n" );
}
