// File: synchronous_daytime_server.cpp
//
// This example show how to use Boost::asio to implement a server application
// with TCP.
#include <ctime>
#include <exception>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

// The function `make_daytime_string() create string which is returned to the
// client
std::string make_day_string(){
   using namespace std;   // For time_t, time and ctime
   time_t now = time(0);
   return ctime(&now);
}

int main() {
   try {
      boost::asio::io_context io_context;
      tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1300));
      for (;;) {
         tcp::socket socket(io_context);
         acceptor.accept(socket);
         std::string message = make_day_string();
         boost::system::error_code ignored_error;
         boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
      }
   }
   catch (std::exception &e){
      std::cerr << e.what() << std::endl;
   }

   return 0;
}
