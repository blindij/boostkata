#include "regexpcpp.h"
#include "ebb_flow.h"
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <vector>

// TODO: replace output with output of just words without explanation
// TODO: add options to program to modify default behavior
// TODO: take input - writing word if explanation is given
// TODO: take input2 - write explanation given word => what if explanation is
// not precise?
//

int main(){
   std::string filename="/Users/bjornlin/exocortex/vimwiki/markdown/gloser.md";
   std::vector<std::string> allentries;
   try {
      auto number_of_entries = read_iso_file(filename, allentries);
      std::vector<boost::tuple<std::string,std::string>> tuple_vector;
   // split the string in word and explanation
      std::string pat("(\\w{1,}) (.*)");
      transform(allentries.begin(), allentries.end(),
                  std::back_inserter(tuple_vector),
                  [&pat](auto & x){
                  boost::regex reg(pat, boost::regex::perl);
                  boost::smatch what;
                  std::string part_one,part_two;
                  if (boost::regex_match(x,what,reg, boost::match_extra)){
                     part_one = what[1];
                     part_two = what[2];
                  } 
                  return boost::make_tuple(part_one, part_two);
                  });
      // auto mtgen = std::mt19937 {};
      boost::random::random_device rng;
      boost::random::uniform_int_distribution<> dist(0,number_of_entries);
      std::cout << "Number of entries: " << number_of_entries << std::endl;
      for (auto i = 0; i < 10; ++i) {
         auto j = dist(rng);
         if (tuple_vector[j].get<0>().size() == 0)
            std::cout << allentries[j] << std::endl;
         else
            std::cout << tuple_vector[j].get<0>() << ", size: " << tuple_vector[j].get<0>().size() << std::endl;
      }

      return 0;
   }
   catch(std::runtime_error& e){
      std::cerr << "Failed to open " << filename << " : " << e.what() << std::endl;
      return 1;
   }
}
