include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(testboost.x 
   test_main.cpp 
   test_boost_libs.cpp
   test_lexical_cast.cpp
   test_unordered_set.cpp
)

target_link_libraries(testboost.x
                     m # C math library
                     boost_kata
)

add_executable(test_boost_iostream.x
   test_main_io.cpp
   test_iostream.cpp
   test_iostream_files.cpp
   test_iostream_shell_comment.cpp
   test_iostream_dict.cpp
   test_iostream_unix2dos.cpp
)

target_link_libraries(test_boost_iostream.x
                     Boost::filesystem
)

add_executable(test_boost_phoenix.x
   test_main_phoenix.cpp
   test_phoenix_basic.cpp
)

