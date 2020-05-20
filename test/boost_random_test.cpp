#include "catch2/catch.hpp"
#include <boost/config.hpp>
#include <boost/random/random_device.hpp>
#include <boost/uniform_int_distribution.hpp>

static const std::string provider = "/dev/urandom";

boost::random_device device(provider);
boost::random::uniform_int distribution<unsigned short> random(1000);

TEST_CASE("Test random return between 1000 and 65535","[thousand]"){
    auto test = random(device);
    REQUIRE( test == 1000);
}