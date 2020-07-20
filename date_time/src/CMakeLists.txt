# ---- create library from source code ----
add_library(ebb_flow SHARED
            ebb_flow.cpp
)

target_link_libraries(ebb_flow
                      Boost::filesystem
)

# ---- create executables from source code ----
add_executable(newebb.x new_ebb.cpp)
target_link_libraries(newebb.x
                      Boost::program_options
)

