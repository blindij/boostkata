add_library(regexcpp regexcpp.cpp)
add_executable(tenwords.x
               tenwords.cpp
)

target_link_libraries(tenwords.x
                      ebb_flow
                      Boost::regex
                      Boost::random
)

add_executable(password.x
               password.cpp
)

target_link_libraries(password.x
                      Boost::random
)
