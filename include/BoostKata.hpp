#ifndef boostkata_header_included
#define boostkata_header_included

namespace boostkata {


}
struct to_long_double_functor: boost::static_visitor<long double> {
   template <class T>
   long double operator()(const T& v) const {
      // Lexical cast has many optimizations including optimizations for
      // situations that usually occur in generic programming, like std::string
      // to std::string or arethmetic type to arithmetic type conversion.
      return boost::lexical_cast<long double>(v);
   }
};

// Throws `boost::bad_lexical_cast` if value of the variant is not convertible
// to `long double`
template <class Variant>
long double to_long_double(const Variant& v) {
   return boost::apply_visitor(to_long_double_functor(), v);
}

struct stringize_functor {
   private:
      std::string& result;
   public:
//      stringize_functor(){}
      explicit stringize_functor(std::string& res) : result(res){}
      template <class T>
      void operator()(const T& v) const{
         result += boost::lexical_cast<std::string>(v);
      }
};

// There is a feature in `Boost::LecialCast` that allows users to use their own
// types  in `lexical_cast`. This feature requires the user to write the
// correct `std::ostream` and `std::istream` operators for their types
//
//
#include <iosfwd>
#include <stdexcept>

// Somewhere in header file there is Negative number, that does not store minus
// sign.
//
class negative_number{
   private:
      unsigned short number_;
   public:
      negative_number(){}   // default constructor
      //explicit negative_number(unsigned short number) : number_(number) {}
      explicit negative_number(unsigned short number) : number_(number) {}
      // operators and function defined
      // ...
      unsigned short value_without_sign() const {
         return number_;
      }
};


template <class ContainerT>
std::vector<long int> container_to_longs(const ContainerT& container) {
   typedef typename ContainerT::value_type value_type;
   std::vector<long int> ret;
   typedef long int (*func_t)(const value_type&);
   func_t f = &boost::lexical_cast<long int, value_type>;
   std::transform(container.begin(), container.end(), std::back_inserter(ret),f);
   return ret;
}

template <class Sequence>
std::string stringize(const Sequence& seq) {
   std::string result;
   boost::fusion::for_each(seq, stringize_functor(result));
   return result;
}

std::ostream& operator<<(std::ostream& os, const negative_number& num);
std::istream& operator>>(std::istream& is, negative_number& num);
#endif 	// boostkata_header_included
