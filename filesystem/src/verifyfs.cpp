// File: verifyfs.cpp
//
// Verify symbolic links 
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <exception>
#include <iostream>
#include <vector>
// ifdef debug
#include <assert.h>

// TODO: wrap assert in #ifdef DEBUG
// TODO: complete help message

namespace fs = boost::filesystem;
namespace opt = boost::program_options;

int main(int argc, char *argv[]){
   std::vector<bool> conf{false,false,false,false,false,false,false,false}; // ["/srv..","tkft4240",symbolic link, content]
   // std::string config_file("nb_verify.cfg");
   opt::options_description desc("All options:");
   desc.add_options()
      ("root,d", opt::value<std::string>()->default_value("/srv/nbgrader/"), "The server directory for exchange and courses")
      ("symdir,s", opt::value<std::string>()->default_value("tkt4240"),"The first course using nbgrader")
      ("help,h", "complete help message");
   opt::variables_map vm;

   // Process config and command-line option
   opt::store(opt::parse_command_line(argc, argv, desc), vm);
   // if (fs::exists(config_file))
   //   opt::store(opt::parse_config_file(config_file, desc), vm);
   opt::notify(vm);

   std::string root=vm["root"].as<std::string>();
   std::string subdir=vm["symdir"].as<std::string>();
   std::string course_path=root+subdir;
   assert(root == "/srv/nbgrader/");
   assert(subdir == "tkt4240");
   assert(course_path == "/srv/nbgrader/tkt4240");


   // Check for existence of /srv/nbgrader or similar
   conf[0] = fs::exists(root);
   conf[1] = fs::exists(subdir);
   conf[2] = fs::is_symlink(subdir);
   if (conf[2])
      try {
      conf[3] = (fs::read_symlink(course_path) == course_path? true : false);
      }
      catch(const fs::filesystem_error& ec){
         std::cout << course_path << "symbolic link do not resolve to real path: " << ec.what() << "." << std::endl;
      }

   if (!conf[0])
      std::cout << root << " does not  exists!" << std::endl;
   if (!conf[1])
      std::cout << course_path << " does not exists!" << std::endl;
   if (!conf[2])
      std::cout << subdir << " does not exists as symbolic link!" << std::endl;
   else
      if (!conf[3])
         std::cout << subdir << " symbolic link points to wrong path!" << std::endl; 
   

   return 0;
}
