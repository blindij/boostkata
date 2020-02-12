cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(boostkata LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(DIRECTORY PROPERTY EP_BASE ${CMAKE_BINARY_DIR}/subprojects)

set(STAGED_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/stage)
message(STATUS "${PROJECT_NAME} staged install: ${STAGED_INSTALL_PREFIX}")

list(APPEND BOOST_COMPONENTS_REQUIRED program_options system)
 set(Boost_MINIMUM_REQUIRED 1.61)
#set(Boost_MINIMUM_REQUIRED 1.72)

add_subdirectory(external/upstream)

include(ExternalProject)
ExternalProject_Add(${PROJECT_NAME}_core
  DEPENDS
    boost_external
  SOURCE_DIR
    ${CMAKE_CURRENT_LIST_DIR}/src
  CMAKE_ARGS
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
    -DCMAKE_CXX_EXTENSIONS=${CMAKE_CXX_EXTENSIONS}
    -DCMAKE_CXX_STANDARD_REQUIRED=${CMAKE_CXX_STANDARD_REQUIRED}
  CMAKE_CACHE_ARGS
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_INCLUDE_PATH:PATH=${BOOST_INCLUDEDIR}
    -DCMAKE_LIBRARY_PATH:PATH=${BOOST_LIBRARYDIR}
  BUILD_ALWAYS
    1
  INSTALL_COMMAND
    ""
  )

# Add Catch2
add_subdirectory(lib/Catch2)

# Add subdirectory test
# add_subdirectory(test)

# --------
add_executable(testboost.x test/test_boost_libs.cpp)
target_link_libraries(testboost.x Catch2::Catch2)
enable_testing()
# add CTest
#include(CTest)
#include(Catch)
#catch_discover_tests(testboost.x)

add_test(
    NAME catch_discover_test
    COMMAND $<TARGET_FILE:testboost.x> --success
)

# Generate the tags file
file (GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hpp)
set_source_files_properties(TAGS PROPERTIES GENERATED true)
add_custom_target(tags
  COMMAND etags --language=c++ --declarations --ignore-indentation
  ${productionSources} ${testSources} ${headers}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# And a custom target as a convenience for running "make unit" as a specific target to support the TDD cycle
add_custom_target(unit
  COMMAND ${CMAKE_BINARY_DIR}/testboost.x
  DEPENDS testboost.x tags
)