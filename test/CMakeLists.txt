include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(testboost.x 
   test_main.cpp 
   test_boost_libs.cpp
   test_lexical_cast.cpp
)

target_link_libraries(testboost.x
                     m # C math library
                     boost_kata
)

add_executable(test_boost_iostream.x
   test_main_io.cpp
   test_iostream.cpp
   test_iostream_files.cpp
)

target_link_libraries(test_boost_iostream.x
                     Boost::filesystem
)
