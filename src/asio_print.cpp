// File: asio_hello_world.cpp
//
// Show how to use a blocking timer
#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code& /*e*/){
   std::cout << "Hello World!" << std::endl;
}

int main() {
   boost::asio::io_context io;  // Use of asio require a io_context object
   boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
   t.async_wait(&print);
   io.run();

   return 0;
}
