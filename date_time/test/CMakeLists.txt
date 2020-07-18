include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test_date_time.x 
   test_main.cpp 
   test_helgeroa_iso.cpp
)

target_link_libraries(test_date_time.x
                      regexcpp
                      Boost::regex
                      Boost::date_time
                      Boost::filesystem
)
