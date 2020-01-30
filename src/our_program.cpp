// File: our_program.cpp
//
// Add human readable help to command line programs
// Example is from "Getting configuration options", in Boost C++
// Application Development Cookbook
//
using namespace std;
#include <boost/program_options.hpp>
//#include <boost/program_options/error.hpp>
#include <iostream>
// Make an alias for boost::program_options
namespace opt = boost::program_options;

int main(int argc, char *argv[]){
   // Describe options
   opt::options_description desc("All options");

   // When adding options, first parameter is a name.
   // Second parameter is a type.
   // Third parameter is a short description.
   desc.add_options()("apples,a", opt::value<int>()->default_value(10), "how many apples do you have")
                     ("oranges,o", opt::value<int>(), "how many oranges do you have")
                     ("name", opt::value<std::string>(), "your name")
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
      opt::store(opt::parse_config_file<char>("apples_oranges.cfg",desc), vm);
   } catch (const opt::reading_file& e) {
      std::cout << "Failed to open file 'apples_oranges.cfg': " << e.what();
   }
   opt::notify(vm);
   if (vm.count("name")){
      std::cout << "Hi, " << vm["name"].as<std::string>() <<   "!\n";
   }
   std::cout << "Fruits count: " << vm["apples"].as<int>() + vm["oranges"].as<int>() << std::endl;
   return 0;
}
