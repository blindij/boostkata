#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "BoostKata.hpp"

using std::cout;
using namespace boost::filesystem;

TEST_GROUP(Boost_Filesystem){
   std::ostringstream outstr;
   char const *ps = "../.gitignore";
   std::vector<path> v;
   void setup(){
      cout << "Global testfile: " << ps << std::endl;
   }
   void teardown(){
   }
};

TEST(Boost_Filesystem, StatusQueryExists){
   CHECK_TRUE(exists(ps));
}

TEST(Boost_Filesystem, StatusQueryNotExists){
   char const *p = "ABRAKADABRA";
   CHECK_FALSE(exists(p));
}

TEST(Boost_Filesystem, StatusQueryNotIsRegularFile){
   char const *p = "../.git";
   CHECK_FALSE(is_regular_file(p));
}

TEST(Boost_Filesystem, StatusQueryIsRegularFile){
   CHECK_TRUE(is_regular_file(ps));
}

TEST(Boost_Filesystem, StatusQueryFileSize){
   CHECK_EQUAL(295, file_size(ps));
}

TEST(Boost_Filesystem, TestExistence){
   char const *ps = "../.git";
   path p(ps);
   CHECK_TRUE(is_directory(p));
}

TEST(Boost_Filesystem, TestContents){
   char const *ps = "../.git";
   path p(ps);
   if (is_directory(p)){
      for (auto x : directory_iterator(p))
         v.push_back(x.path());
      std::sort(v.begin(),v.end());
      for (auto x : v )
         outstr << x.filename() << " ";
      CHECK_EQUAL("\"COMMIT_EDITMSG\" \"HEAD\" \"config\" \"description\" \"hooks\" \"index\" \"info\" \"logs\" \"objects\" \"refs\" ", outstr.str());
   } else FAIL("The file directory is false\n");

}
