#include "catch2/catch.hpp"
#include <algorithm>                         // copy, min
#include <cstring>
#include <ios>
#include <iosfwd>                            // streamsize
#include <boost/iostreams/categories.hpp>    // source_tag
#include <ostream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

namespace io = boost::iostreams;

class my_source {
   public:
      typedef char char_type;
      typedef io::source_tag category;

      std::streamsize read(char* s, std::streamsize n){
         // Read up to n characters from the underlying data source
         // into the buffer s, returning the number of characters
         // read; return -1  to indicate EOF
      }
      
      /* Other members */
};

namespace boost { namespace iostreams { namespace example {

template <typename Container>
class container_source {
   private:
   typedef typename Container::size_type size_type;
   Container& container_;
   size_type  pos_;

   public:
      typedef typename Container::value_type char_type;
      typedef boost::iostreams::source_tag                    category;
      container_source(Container& container) : container_(container), pos_(0) { }
      std::streamsize read(char_type* s, std::streamsize n) {
            using namespace std;
            streamsize amt = static_cast<streamsize>(container_.size() - pos_);
            streamsize result = (min) (n, amt);
            if (result != 0) {
               std::copy( container_.begin() + pos_, container_.begin() + pos_ + result, s);
               pos_ += result;
               return result;
            } else {
               return -1; // EOF
            }
      }
      Container& container() { return container_; }
};

   
} } } // End namespace boost::iostream::example

TEST_CASE("Read from a container_source","[iostream][read]"){
   namespace io = boost::iostreams;
   namespace ex = boost::iostreams::example;
   typedef ex::container_source<std::string> string_source;
   std::string                     input = "Hello World!";
   std::string                     output;
   io::stream<string_source>  in(input);
   getline(in, output);
   REQUIRE( input == output);
}

TEST_CASE("Write to log.txt","[iostream][log]"){
   io::stream_buffer<io::file_sink> buf("log.txt");
   std::ostream out(&buf);
   // out writes to log.txt
   out << "Hello World!\n";
}
