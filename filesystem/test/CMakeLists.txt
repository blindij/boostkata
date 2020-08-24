add_executable(test_filesystem.x
   test_main.cpp
)

target_link_libraries(test_filesystem.x
    Boost::filesystem
)

