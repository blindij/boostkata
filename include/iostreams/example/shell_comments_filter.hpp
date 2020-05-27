// File: shell_comments_filter.hpp
//
// A Boost::iostream input filter which removes shell-style comments
// The code is from the documentation of Boost.iostreams. It is also
// found in ${BOOST_ROOT}/libs/iostream/example/shell_comments_filter.hpp
//
#ifndef SHELL_COMMENTS_FILTER_HPP
#define SHELL_COMMENTS_FILTER_HPP
#include <iostream>
#include <cstdio>
#include <boost/iostreams/filter/stdio.hpp>

namespace boost { namespace iostreams { namespace example {

class shell_comments_input_filter : public input_filter {
   public:
      explicit  shell_comments_input_filter(char comment_char = '#') : comment_char_(comment_char), skip_(false){}
      template<typename Source>
      int get(Source& src) {
         int c;
         while (true) {
            if ((c = boost::iostreams::get(src)) == EOF || c == WOULD_BLOCK)
               break;
            skip_ = c == comment_char_?
               true :
               c == '\n' ? false : skip_;
            if (!skip_)
               break;
         }
         return c;
      }

      template<typename Source>
      void close(Source&) {skip_ = false; }

   private:
      char comment_char_;
      bool skip_;
};

class shell_comments_output_filter : public output_filter {
   public:
      explicit shell_comments_output_filter(char comment_char = '#') : comment_char_(comment_char), skip_(false) { }
      template<typename Sink>
      bool put(Sink& dest, int c) {
         skip_ = c == comment_char_ ? true : c == '\n' ? false : skip_ ;

         if (skip_)
            return true;

         return iostreams::put(dest,c);
      }

      template<typename Source>
      void close(Source&) {skip_ = false; }
   private:
      char comment_char_;
      bool skip_;
};
} } }  // End namespace boost::iostreams::example
#endif  // SHELL_COMMENTS_FILTER_HPP
