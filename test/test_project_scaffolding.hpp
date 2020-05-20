// file: project_test_scaffolding.hpp
//
// File with simpler test to verify concepts not easily understood
// when using the Boost library
#ifndef TEST_PROJECT_SCAFFOLDING_HPP
#define TEST_PROJECT_SCAFFOLDING_HPP

struct bad_hmean {
   private:
      double v1;
      double v2;
   public:
      bad_hmean(double a = 0, double b = 0) : v1(a), v2(b){}
      void mesg();
};

inline void bad_hmean::mesg(){
   std::cout << "hmean(" << v1 << ", " << v2 << "):"
               << "invalid arguments: a = -b\n";
}

struct bad_gmean {
   public:
      double v1;
      double v2;
      bad_gmean(double a = 0, double b = 0) :v1(a), v2(b){}
      const char * mesg();
};

inline const char * bad_gmean::mesg() {
   return "gmean() arguments shoulb be >= 0\n";
}

double hmean(double a, double b){
   if (a == -b) {
      throw "bad hmean() arguments: a = -b not allowd";
   }
   return 2.0 * a * b/ (a + b);
}

double gmean(double a, double b) {
   throw bad_gmean(a,b);
   return std::sqrt(a * b);
}

TEST_CASE("testing hmean throwing object","[exception][hmean][object]"){
   REQUIRE_THROWS_AS(throw bad_gmean(), bad_gmean);
}

TEST_CASE("testing may own throw","[exception][hmean]"){
   REQUIRE_THROWS( hmean(10, -10));
}

TEST_CASE("Hello World","[hw]"){
    std::ostringstream myout;
    myout << "Hello World!" << std::endl;
    REQUIRE( myout.str() == "Hello World!\n");
}

#endif // end TEST_PROJECT_SCAFFOLDING_HPP
