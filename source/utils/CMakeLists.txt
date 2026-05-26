add_library(utils
    src/math_utils.cpp
    src/readwrite_traj.cpp
)

target_include_directories(utils
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
