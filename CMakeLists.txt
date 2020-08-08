cmake_minimum_required (VERSION 3.9 FATAL_ERROR)
project (boostkata-kata
         DESCRIPTION "Using Boost libraries and headers as an exercise."
         LANGUAGES CXX
)

# ...settings...
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find Boost
find_package(Boost 1.72 REQUIRED COMPONENTS date_time filesystem program_options random regex)

# include project header files including
# Catch2 which is in subdirectory ./include/catch2
include_directories(include)

# ---- add subdirectory wit source files ----
add_subdirectory(src)

# ---- add subdirectory with tests ----
add_subdirectory(test)

# ---- add subdirectory regex
add_subdirectory(regex)

# ---- add subdirectory date_time
add_subdirectory(date_time)

enable_testing()

add_test(
   NAME setup
   COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/setup.sh
)
set_tests_properties(
   setup
   PROPERTIES
      FIXTURES_SETUP test_boost_fixtures
)

add_test(
   NAME test_boost
   COMMAND $<TARGET_FILE:testboost.x>
)

add_test(
   NAME test_boost_iostream
   COMMAND $<TARGET_FILE:test_boost_iostream.x>
)
set_tests_properties(
   test_boost_iostream
   PROPERTIES
      FIXTURES_REQUIRED test_boost_fixtures
)

add_test(
   NAME test_boost_regex
   COMMAND $<TARGET_FILE:test_boost_regex.x>
)

add_test(
   NAME cleanup
   COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/cleanup.sh
)
set_tests_properties(
   cleanup
   PROPERTIES
      FIXTURES_CLEANUP test_boost_fixtures
)

# ------ Boost::date_time setup
add_test(
   NAME date_time_setup
   COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/date_time/test/setup.sh
)
set_tests_properties(
   date_time_setup
   PROPERTIES
      FIXTURES_SETUP test_date_time_fixtures
)
add_test(
   NAME test_date_time
   COMMAND $<TARGET_FILE:test_date_time.x> -s
)
set_tests_properties(
   test_date_time
   PROPERTIES
      FIXTURES_REQUIRED test_date_time_fixtures
)
add_test(
   NAME date_time_cleanup
   COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/date_time/test/cleanup.sh
)
set_tests_properties(
   date_time_cleanup
   PROPERTIES
      FIXTURES_CLEANUP test_date_time_fixtures
)
