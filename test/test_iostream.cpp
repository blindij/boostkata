#include "catch2/catch.hpp"
#include <ostream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

namespace io = boost::iostreams;

TEST_CASE("Write to log.txt","[iostream][log]"){
   io::stream_buffer<io::file_sink> buf("log.txt");
   std::ostream out(&buf);
   // out writes to log.txt
   out << "Hello World!\n";
}
