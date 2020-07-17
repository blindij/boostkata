// File: test_helgeroa_iso.cpp
//
// Read the file helgeroaiso.txt which contain time points for
// ebb and flow at Helgeroa in a ISO time format
#include "catch2/catch.hpp"
#include <sstream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;
namespace io = boost::iostreams;

TEST_CASE("Read from helgeroaiso.txt","[date_time][fileread]"){
  string file("helgeroaiso.txt");
  REQUIRE(fs::exists(file));
  SECTION("Read from the file"){
     string result;
     io::stream_buffer<io::file_source> buf(file);
     istream                            in(&buf);
     getline(in,result);
     REQUIRE( result == "20200716T0206:63");
  }
}
