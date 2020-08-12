// File: asio_hello_world.cpp
//
// Show how to use a blocking timer
#include <iostream>
#include <boost/asio.hpp>

int main() {
   boost::asio::io_context io;  // Use of asio require a io_context object
   boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
   t.wait();
   std::cout << "Hello World!" << std::endl;

   return 0;
}
