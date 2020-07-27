// File: ebb.cpp
//
// Add human readable help to command line programs
// Example is from "Getting configuration options", in Boost C++
// Application Development Cookbook
//
#include "ebb_flow.h"
#include <boost/program_options.hpp>
#include <boost/tuple/tuple.hpp>
#include <iostream>

using namespace std;

// Make an alias for boost::program_options
namespace opt = boost::program_options;
namespace fs = boost::filesystem;
namespace pt = boost::posix_time;
namespace tp = boost::tuples;

int main(int argc, char *argv[]){
   // Describe options
   opt::options_description desc("All options");

   // When adding options, first parameter is a name.
   // Second parameter is a type.
   // Third parameter is a short description.
   desc.add_options()
      ("primary,p", opt::value<string>()->default_value("kristiansund"), "The standard harbour")
      ("secondary,s", opt::value<string>()->default_value("uthaug"), "The secondary harbour under the standard")
      ("minutes,m", opt::value<int>()->default_value(15), "Positive or negative minutes to use as correction")
      ("heightfactor,hf", opt::value<double>()->default_value(1.14), "A correction factor for the height")
      ("delta,d", opt::value<int>()->default_value(0), "A delta [cm] to add to the corrected height. For most harbours it is 0")
      ("help","produce help message");

   // Variable to store our command line arguments 
   opt::variables_map vm;

   // Parsing and storing arguments
   opt::store(opt::parse_command_line(argc, argv, desc), vm);
   opt::notify(vm);
   if (vm.count("help")){
      std::cout << desc << "\n";
      return 1;
   }
   
   // Adding missing options from "apples_oranges.cfg"
   // config file. You can also provide an istreamable object
   // as a first parameter ofr 'parse_config_file'. 'char' templated
   // parameter will be passed to underlying std::basic_stream object
   try {
      opt::store(opt::parse_config_file<char>("ebb.cfg",desc), vm);
   } catch (const opt::reading_file& e) {
      std::cerr << "Failed to open file 'ebb.cfg': " << e.what() << std::endl;
   }
   double heightfactor = vm["heightfactor"].as<double>();
   int distance_delta = vm["delta"].as<int>();
   pt::minutes adjust_min(vm["minutes"].as<int>());
   // std::cout << "Correction in minutes: " << vm["minutes"].as<int>() << " Height correction factor: " << vm["heightfactor"].as<double>() << std::endl;
   std::cout << "Correction in minutes: " << adjust_min << " Height correction factor: " << heightfactor << std::endl;
   string filename = vm["primary"].as<string>() + "iso.txt";
   string outputfile = vm["secondary"].as<string>() + ".txt";
   vector<string> timepoints;
   vector<tp::tuple<string,string>> timepoint_height_vector;
   vector<tp::tuple<pt::ptime, int>> result;
   try {
   size_t number_of_entries = read_iso_file(filename, timepoints);
   timepoints.pop_back();

// split the string in timepoint and height 
   std::string pat("(\\d{8}T\\d{4}):(\\d{2,3})");
   transform(timepoints.begin(), timepoints.end(),
               std::back_inserter(timepoint_height_vector),
               [&pat](auto & x){
               boost::regex reg(pat, boost::regex::perl);
               boost::smatch what;
               std::string part_one,part_two;
               if (boost::regex_match(x,what,reg, boost::match_extra)){
                  part_one = what[1];
                  part_two = what[2];
               } 
               return tp::make_tuple(part_one, part_two);
               });


// create boost::posix_time::minutes out of timepoint(string)
   std::transform(timepoint_height_vector.begin(),
                  timepoint_height_vector.end(),
                  std::back_inserter(result), 
                  [](auto & x){
                     pt::ptime t1(pt::from_iso_string(get<0>(x)));
                     istringstream height(get<1>(x));
                     int tmp;
                     height >> tmp;
                     return tp::make_tuple(t1, tmp);
                   });

// transform the timepoint and height
//
   vector<tp::tuple<pt::ptime, int>> transformed;
   transform(result.begin(),
             result.end(),
             std::back_inserter(transformed),
             [&heightfactor, &distance_delta, & adjust_min](auto & x){
                 return tp::make_tuple(get<0>(x) + adjust_min,  get<1>(x) * heightfactor + distance_delta);
                              });
   cout << number_of_entries - 1<< " read from " << filename << std::endl;
   std::cout << "Correction in minutes: " << vm["minutes"].as<int>() << std::endl;
   std::cout << "Height correction factor: " << vm["heightfactor"].as<double>() << std::endl;
   if (vm["delta"].as<int>() != 0) std::cout << "Additional height to add: [cm] " << vm["delta"].as<int>() << std::endl;
   number_of_entries  = write_iso_file(outputfile, transformed);
   cout << number_of_entries << " written to " << outputfile << std::endl;
   return 0;
   }
   catch(std::runtime_error& e){
      std::cerr << "Failed to open " << filename << " : " << e.what() << std::endl;
      return 1;
   }
}
