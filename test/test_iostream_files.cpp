#include "catch2/catch.hpp"
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/filesystem.hpp>

using namespace std;
namespace io = boost::iostreams;
namespace fs = boost::filesystem;

TEST_CASE("Read from gloser.txt","[iostream][fileread]"){
   string ps("gloser.txt");
   REQUIRE(fs::exists(ps));
}

TEST_CASE("Write to log.txt","[iostream][log]"){
   string ps("log.txt");
   io::stream_buffer<io::file_sink> buf(ps);
   std::ostream out(&buf);
   // out writes to log.txt
   out << "Hello World!\n";
   out.flush();
   REQUIRE(boost::filesystem::file_size(ps) == 13);
   SECTION("Remove log.txt file"){
      REQUIRE(fs::remove(ps));
   }
}
