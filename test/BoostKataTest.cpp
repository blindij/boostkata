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
   std::vector<path> v;
   void setup(){
   }
   void teardown(){
   }
};

TEST(Boost_Filesystem, TestExistence){
   char const *ps = "/Users/bjornlin/projects/boostkata";
   path p(ps);
   CHECK_TRUE(is_directory(p));
}

TEST(Boost_Filesystem, TestContents){
   char const *ps = "/Users/bjornlin/projects/boostkata";
   path p(ps);
   if (is_directory(p)){
      for (auto x : directory_iterator(p))
         v.push_back(x.path());
      std::sort(v.begin(),v.end());
      for (auto x : v )
         outstr << x.filename() << " ";
      CHECK_EQUAL("\".build\" \".gitignore\" \"CMakeLists.txt\" \"LICENSE\" \"README.md\" \"include\" \"lib\" \"src\" \"test\" ", outstr.str());
   } else FAIL("The file directory is false\n");

}
