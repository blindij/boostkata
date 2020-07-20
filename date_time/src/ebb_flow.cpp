// File: ebb_flow.cpp
//
// Methods for calculating and writing time points for ebb and flow at other
// places than the standard harbours.
//
#include "ebb_flow.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

namespace fs = boost::filesystem;
namespace io = boost::iostreams;

void new_datetime_height(boost::posix_time::minutes min, double heightfactor, boost::tuple<boost::posix_time::ptime, int>& tho){
   get<0>(tho) = tho.get<0>() + min;
   get<1>(tho) = tho.get<1>() * heightfactor;
}

boost::tuple<ptime,int> string2datetime_height(const string& s, string& cm_height) {
   ptime t1(from_iso_string(s));
   istringstream height(cm_height);
   int tmp;
   height >> tmp;
   return boost::make_tuple(t1, tmp);
}

size_t read_iso_file(std::string& filename,std::vector<std::string>& vecent){
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

size_t write_iso_file(std::string& filename, std::vector<boost::tuple<boost::posix_time::ptime, int>>& timeheightobjects){
   size_t written = 0;
   io::stream_buffer<io::file_sink> buf(filename);
   std::ostream out(&buf);
   for_each(begin(timeheightobjects),end(timeheightobjects),
      [&out, &written](boost::tuple<boost::posix_time::ptime,int> n) { out << n.get<0>() << ":" << n.get<1>() << std::endl;
      written++;
      });
   out.flush();
   return written;
}
