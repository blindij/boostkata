include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test_date_time.x 
   test_main.cpp 
)

target_link_libraries(test_date_time.x
                      Boost::date_time
)
