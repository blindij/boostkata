//
// Created by Bjørn Lindi on 2020-01-05.
//
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"


TEST_CASE("Hello World","[hw]"){
    std::ostringstream myout;
    myout << "Hello World!" << std::endl;
    REQUIRE( myout.str() == "Hello World!\n");
}
