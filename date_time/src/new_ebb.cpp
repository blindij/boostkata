// File: our_program.cpp
//
// Add human readable help to command line programs
// Example is from "Getting configuration options", in Boost C++
// Application Development Cookbook
//
#include <boost/program_options.hpp>
//#include <boost/program_options/error.hpp>
#include <iostream>
using namespace std;
// Make an alias for boost::program_options
namespace opt = boost::program_options;

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
      ("delta,d", opt::value<int>()->implicit_value(0), "A delta [cm] to add to the corrected height. For most harbours it is 0")
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
      std::cout << "Failed to open file 'ebb.cfg': " << e.what();
   }
   opt::notify(vm);
   if (vm.count("primary")){
      std::cout << "Standard harbours is " << vm["primary"].as<std::string>() <<   ".\n";
   }
   std::cout << "Correction in minutes: " << vm["minutes"].as<int>() << " Height correction factor: " << vm["heightfactor"].as<double>() << std::endl;
   return 0;
}
