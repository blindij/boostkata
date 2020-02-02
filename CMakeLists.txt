cmake_minimum_required (VERSION 3.9 FATAL_ERROR)
project (boostkata-kata LANGUAGES CXX)

# ...settings...
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BOOST_ROOT "/Users/bjornlin/local/boost_1.72.0")
set(Catch2_DIR "/Users/bjornlin/local/CMake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Catch2/contrib")
# Include CppUTest from /lib fodler. The flag is necessary to make it
# use the same flags as the top level (ie this) build
# option(CPPUTEST_FLAGS OFF)
# add_subdirectory(lib/cpputest)

# Search for Boost
find_package(Boost 1.69 REQUIRED COMPONENTS program_options)

# Add Catch2
add_subdirectory(lib/Catch2)
# For the sake of form, and to give an idea of the sort of setup you'd
# find in a "real world" project, we're keeping the sources separate,
# and creating a separate archive
#file (GLOB productionSources src/*.cpp)
#add_library (boostkata STATIC ${productionSources})
#target_include_directories (boostkata PRIVATE ${PROJECT_SOURCE_DIR}/include)
add_executable(our_program src/our_program.cpp)
target_link_libraries(our_program Boost::program_options)

add_executable(boostany.x src/boostany.cpp)

# add test 
# add_subdirectory(test)
add_executable(testboost.x test/test_boost_libs.cpp)
target_link_libraries(testboost.x Catch2::Catch2)
enable_testing()
# add CTest
# include(CTest)
# include(Catch)
# catch_discover_tests(testboost.x)

add_test(
    NAME catch_discover_test
    COMMAND $<TARGET_FILE:testboost.x> --success
)

# target_link_libraries(boostany.x Boost::any)
# file (GLOB testSources test/*.cpp)
# add_executable(boostkata.x ${productionSources})
# target_link_libraries(boostkata.x Boost::filesystem)

#add_executable (boostkatatest ${testSources})
#target_link_libraries (boostkatatest boostkata CppUTest CppUTestExt Boost::filesystem)
#target_include_directories (boostkatatest PRIVATE ${PROJECT_SOURCE_DIR}/lib/cpputest/include)
#target_include_directories (boostkatatest PRIVATE ${PROJECT_SOURCE_DIR}/include)

# # This enables the "make test" target, although for TDD it's likely
# # you'll want to use the "make unit" target.
# enable_testing ()

# # Add the unit tests executable 
# add_test (Unit boostkatatest)


# # Generate the tags file
# file (GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hpp)
# set_source_files_properties(TAGS PROPERTIES GENERATED true)
# add_custom_target(tags
#   COMMAND etags --language=c++ --declarations --ignore-indentation
#   ${productionSources} ${testSources} ${headers}
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR})


# # And a custom target as a convenience for running "make unit" as a
# # specific target to support the TDD cycle
# add_custom_target(unit
#   COMMAND ${CMAKE_BINARY_DIR}/boostkatatest -c
#  DEPENDS boostkatatest  tags )
#