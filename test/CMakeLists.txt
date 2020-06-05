add_executable(testboost.x test_boost_libs.cpp)
enable_testing()
## add CTest
#include(CTest)
#include(Catch)
#catch_discover_tests(testboost.x)
#
#add_test(
#    NAME catch_discover_test
#    COMMAND $<TARGET_FILE:testboost.x> --success
#)
