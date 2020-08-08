// File: password.cpp
//
// Generating a random password of length 8
//
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <iostream>

int main() {
   std::string chars("abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "1234567890"
                     "!@#$%^&*()"
                     "`~-_=+[{]}\\|;:'\",<.>/? ");
   boost::random::random_device rng;
   boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
   for(int i = 0; i < 12; ++i){
      std::cout << chars[index_dist(rng)];
   }
   std::cout << std::endl;
}
