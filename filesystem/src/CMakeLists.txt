add_executable(verifyfs.x verifyfs.cpp)
target_link_libraries(verifyfs.x 
                        Boost::filesystem
                        Boost::program_options
)

add_executable(filesys.x filesys_example.cpp)
target_link_libraries(filesys.x Boost::filesystem)
