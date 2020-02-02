add_executable(testboost.x test_boost_libs.cpp)
target_link_libraries(testboost.x Catch2::Catch2)
enable_testing()
# add CTest
include(CTest)
include(Catch)
catch_discover_tests(testboost.x)

add_test(
    NAME catch_discover_test
    COMMAND $<TARGET_FILE:testboost.x> --success
)