include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(testboost.x 
   test_main.cpp test_boost_libs.cpp
   test_lexical_cast.cpp
   test_iostream.cpp
)
target_link_libraries(testboost.x
                     m # C math library
                     boost_kata
)
