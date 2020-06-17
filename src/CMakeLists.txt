# ---- create library from source code ----
add_library(boost_kata lexical_cast.cpp)
add_library(regexcpp regexcpp.cpp)
# ---- create executables ----
add_executable(synch_daytime_server.x synchronous_daytime_server.cpp)
add_executable(synch_daytim.x synchronous_daytime_client.cpp)
add_executable(synch.x synchronize_handlers.cpp)
target_link_libraries(synch.x Boost::thread)
add_executable(classp.x asio_class_printer.cpp)
add_executable(second.x once_a_second.cpp)
add_executable(asio_hw.x asio_hello_world.cpp)
add_executable(asio_print.x asio_print.cpp)
add_executable(our_program our_program.cpp)
target_link_libraries(our_program Boost::program_options)

add_executable(boostany.x boostany.cpp)


