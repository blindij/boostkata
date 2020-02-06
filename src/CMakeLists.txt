cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(boostkata LANGUAGES CXX)

# find_package(Boost 1.61 REQUIRED COMPONENTS any program_options variant)
find_package(Boost 1.61 REQUIRED COMPONENTS program_options )
add_executable(our_program our_program.cpp)
target_link_libraries(our_program PUBLIC Boost::program_options)

add_executable(boostany.x boostany.cpp)
        
