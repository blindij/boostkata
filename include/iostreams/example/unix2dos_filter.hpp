// File: unix2dos_filter.hpp
//
// Boost::iostream example of a unix2dos filter. The example is from the
// Boost::iostream tutorial
#ifndef BOOST_IOSTREAMS_UNIX2DOS_FILTER_HPP
#define BOOST_IOSTREAMS_UNIX2DOS_FILTER_HPP

#include <cassert>
#include <cstdio>      // EOF
#include <iostream>    // cin, cout
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/filter/stdio.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/invert.hpp>

namespace boost { namespace iostreams { namespace example {
class unix2dos_input_filter : public input_filter   {
public:
   typedef char               char_type;
   typedef input_filter_tag   category;
   unix2dos_input_filter() : has_linefeed_(false) { }

   template<typename Source>
   int get(Source& src){
      // Handle unfinished business
      if (has_linefeed_) {
         has_linefeed_ = false;
         return '\n';
      }
      
      // Forward all characters except '\n'
      int c;
      if ((c = iostreams::get(src)) == '\n'){
         has_linefeed_ = true;
         return '\r';
      }

      return c;
   }

   template<typename Source>
   void close(Source&) {has_linefeed_ = false; }

private:
   bool has_linefeed_; 
};

// } } } // End namespace boost::iostreams::example

class unix2dos_output_filter : public output_filter {
private:
      template<typename Sink>
      bool put_char(Sink& dest, int c){
         bool result;
         if ((result = iostreams::put(dest, c)) == true) {
            has_linefeed_ = c == '\r' ? true : c == '\n' ? false : has_linefeed_;
         }
         return result;
      }

      bool has_linefeed_;

public:
      unix2dos_output_filter() : has_linefeed_(false) { }

      template<typename Sink>
      bool put(Sink& dest, int c){
         if (c == '\n')
             return has_linefeed_ ? put_char(dest,'\n') :
               put_char(dest, '\r') ? this->put(dest, '\n') : false;
         return iostreams::put(dest,c);
      }

      template<typename Sink>
      void close(Sink&) { has_linefeed_ = false; }

};
} } }  // End namespace example, iostreams, boost

#endif // BOOST_IOSTREAMS_UNIX2DOS_FILTER_HPP
