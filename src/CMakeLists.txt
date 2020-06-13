# ---- create library from source code ----
add_library(boost_kata lexical_cast.cpp)
add_library(regexcpp regexcpp.cpp)
# ---- create executables ----
   add_executable(asio_hw.x asio_hello_world.cpp)
add_executable(our_program our_program.cpp)
target_link_libraries(our_program Boost::program_options)

add_executable(boostany.x boostany.cpp)


