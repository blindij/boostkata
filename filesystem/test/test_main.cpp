//
// Created by Bjørn Lindi on 19/04/2020.
//
#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include <boost/filesystem.hpp>


TEST_CASE("Create directory","[filesystem][create]"){
   std::string const p("test_subdirectory");
   REQUIRE(boost::filesystem::create_directory(p));
   SECTION("Check that the subdirectory exists"){
      std::string const p2("test_symlink");
      boost::filesystem::create_symlink(p,p2);
      REQUIRE(boost::filesystem::is_symlink(p2));
      SECTION("Remove symlink"){
         REQUIRE(boost::filesystem::remove(p2));
         SECTION("Remove subdirectory"){
          REQUIRE(boost::filesystem::remove(p));
         }
      }
   }
}

