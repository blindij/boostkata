// File: ebb_flow.cpp
//
// Methods for calculating and writing time points for ebb and flow at other
// places than the standard harbours.
//
#include "ebb_flow.h"

using namespace std;
//using namespace boost::gregorian;

namespace pt = boost::posix_time;
namespace fs = boost::filesystem;
namespace io = boost::iostreams;

size_t read_iso_file(std::string& filename,std::vector<std::string>& vecent){
   if ( !fs::exists(filename)) throw exception();
   string result;
   io::stream_buffer<io::file_source> buf(filename);
   istream in(&buf);
   if (fs::exists(filename)){
      while(in){
         getline(in,result);
         vecent.push_back(result);
      }
   }
   return vecent.size();
}

size_t write_iso_file(std::string& filename, std::vector<boost::tuple<pt::ptime, int>>& timeheightobjects){
   size_t written = 0;
   io::stream_buffer<io::file_sink> buf(filename);
   std::ostream out(&buf);
   for_each(begin(timeheightobjects),end(timeheightobjects),
      [&out, &written](boost::tuple<pt::ptime,int> n) { out << n.get<0>() << ":" << n.get<1>() << std::endl;
      written++;
      });
   out.flush();
   return written;
}
