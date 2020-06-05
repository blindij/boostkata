// File: dictionary_filter.hpp
//
// Example from the Boost.iostream tutorial
//
#ifndef IOSTREAMS_DICTIONARY_FILTER_HPP
#define IOSTREAMS_DICTIONARY_FILTER_HPP
#include <algorithm>                // swap
#include <cstdio>                   // EOF
#include <iostream>
#include <cctype>
#include <map>
#include <boost/config.hpp>         // BOOST_NO_STDC_NAMESPACE
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/operations.hpp>
#include <ostream>

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std {
   using ::isalpha;
   using ::isupper;
   using ::toupper;
   using ::tolower;
}
#endif

namespace boost { namespace iostreams { namespace example {

class dictionary {
   public:
      typedef std::map<std::string, std::string> map_type;
      void add(std::string key, const std::string& value);
      void replace(std::string& key);
      const map_type::iterator begin();
      const map_type::iterator end();
// output operator for dictionary 
      friend std::ostream& operator<<(std::ostream& strm, const dictionary& d); 

   private:
      void tolower(std::string& str);
      map_type map_;

};

// --------------- Implementation of dictionary -------------------
inline void dictionary::add(std::string key, const std::string& value) {
   tolower(key);
   map_[key] = value;
}

inline void dictionary::replace(std::string& key){
   using namespace std;
   string copy(key);
   tolower(copy);
   map_type::iterator it = map_.find(key);
   if (it == map_.end())
      return;
   string& value = it->second;
   if (!value.empty() && !key.empty() && std::isupper((unsigned char) key[0]))
      value[0] = std::toupper((unsigned char) value[0]);
   key = value;
   return;
}

inline void dictionary::tolower(std::string& str) {
   for (std::string::size_type z = 0, len = str.size(); z < len; ++z){
      str[z] = std::tolower((unsigned char) str[z]);
   }
}

inline const dictionary::map_type::iterator dictionary::begin(){ return map_.begin();}

inline const dictionary::map_type::iterator dictionary::end(){ return map_.end();}

std::ostream & operator<<(std::ostream & os, dictionary & d){
   dictionary::map_type::iterator pos;
   for( pos = d.begin(); pos != d.end(); pos++) os << "(" << pos->first << ": " << pos->second << ")" << std::endl;
   return os;
}
}}}

#endif // IOSTREAMS_DICTIONARY_FILTER_HPP
