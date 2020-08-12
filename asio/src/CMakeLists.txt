add_executable(synch_daytime_server.x synchronous_daytime_server.cpp)
target_link_libraries(synch_daytime_server.x Boost::thread)

add_executable(synch_daytime.x synchronous_daytime_client.cpp)
target_link_libraries(synch_daytime.x Boost::thread)

add_executable(synch.x synchronize_handlers.cpp)
target_link_libraries(synch.x Boost::thread)

add_executable(classp.x asio_class_printer.cpp)
add_executable(second.x once_a_second.cpp)
add_executable(asio_hw.x asio_hello_world.cpp)
add_executable(asio_print.x asio_print.cpp)
