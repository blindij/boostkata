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
find_package(Boost 1.72 REQUIRED COMPONENTS program_options)

# include project header files including
# Catch2 which is in subdirectory ./include/catch2
include_directories(include)

# ---- add subdirectory wit source files ----
add_subdirectory(src)

# ---- add subdirectory with tests ----
add_subdirectory(test)

