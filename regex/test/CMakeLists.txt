add_executable(test_boost_regex.x
   test_main_regex.cpp
)

target_link_libraries(test_boost_regex.x
    Boost::regex
    regexcpp
)

