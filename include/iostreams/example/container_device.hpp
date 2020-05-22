#include <algorithm>                         // copy, min
#include <cstring>
#include <ios>
#include <iosfwd>                            // streamsize
#include <boost/iostreams/categories.hpp>    // source_tag, sinkt_tag
#include <ostream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

namespace io = boost::iostreams;

class my_device {
   typedef char                  char_type;
   typedef io::seekable_device_tag   category;

   std::streamsize read(char* s, std::streamsize n) {
      // Read up to n characters from the underlying data source
      // into the buffer s, returning the number of characters
      // read; return -1 to indicate EOF
   }

   std::streamsize write(const char* s, std::streamsize n){
      // Write up to n characters to the underlying
      // data sink into the buffer s, returning the 
      // number of characters written
   }

   io::stream_offset seek(io::stream_offset off, std::ios_base::seekdir way){
      // Seek to position off and return the new stream
      // position. The argument way indicates how off is
      // interpreted:
      //  - std::ios_base::beg indicates an offset from the 
      //    sequence beginning
      //  - std::ios_base::cur indicates an offset from the
      //    current character position
      //  - std::ios_base::end indicates an offset from the
      //    sequence end
   }

   /* Other members */
};

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

class my_sink {
   public:
      typedef char                char_type;
      typedef io::sink_tag        category;

      std::streamsize write(const char* s, std::streamsize n) {
         // Write up to n characters to the underlying
         // data sink into the buffer s, returning the 
         // number of characters written
      }

      /* Other members */
};

namespace boost { namespace iostreams { namespace example {

template <typename Container>
class container_device {
   public:
      typedef typename Container::value_type char_type;
      typedef seekable_device_tag            category;
      container_device(Container& container) : container_(container), pos_(0) { }

      std::streamsize read(char_type* s, std::streamsize n) {
         using namespace std;
         streamsize amt = static_cast<streamsize>(container_.size() - pos_);
         streamsize result = (min) (n, amt);
         if (result != 0) {
            std::copy( container_.begin() + pos_, container_.begin() + pos_ + result, s);
            pos_ += result;
            return result;
         } else {
            return -1; //EOF
         }
      }

      std::streamsize write(const char_type* s, std::streamsize n){
         using namespace std;
         streamsize result = 0;
         if (pos_ != container_.size()) {
            streamsize amt = static_cast<streamsize>(container_.size() - pos_);
            result = (min)(n, amt);
            std::copy(s, s + result, container_.begin() + pos_);
            pos_ += result;
         }
         if (result < n){
            container_.insert(container_.end(), s + result, s + n);
            pos_ = container_.size();
         }
         return n;
      }
      
      stream_offset seek(stream_offset off, std::ios_base::seekdir way) {
         using namespace std;

         // Determine new value of pos_
         stream_offset next;
         if (way == ios_base::beg) {
            next = off;
         } else if (way == ios_base::cur){
            next = pos_ + off;
         } else if (way == ios_base::end){
            next = container_.size() + off - 1;
         } else {
            throw ios_base::failure("bad seek direction");
         }

         // Check for errors
         if (next < 0 || next >= static_cast<stream_offset>(container_.size()))
            throw ios_base::failure("bad seek offset");

         pos_ = next;
         return pos_;
      }
   private:
      typedef typename Container::size_type           size_type;
      Container& container_;
      size_type pos_;
};


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

template <typename Container>
class container_sink {
   private:
      Container& container_;
   public:
      typedef typename Container::value_type char_type;
      typedef sink_tag                       category;
      container_sink(Container& container) : container_(container) {}
      std::streamsize write(const char_type* s, std::streamsize n){
         container_.insert(container_.end(), s, s + n);
         return n;
      }
      Container& container() {return container_;}
};
   
} } } // End namespace boost::iostream::example


