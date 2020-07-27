# ---- create library from source code ----
add_library(ebb_flow SHARED
            ebb_flow.cpp
)

target_link_libraries(ebb_flow
                      Boost::filesystem
)

# ---- create executables from source code ----
add_executable(ebb.x ebb.cpp)
target_link_libraries(ebb.x
                      ebb_flow
                      Boost::regex
                      Boost::date_time
                      Boost::program_options
)

