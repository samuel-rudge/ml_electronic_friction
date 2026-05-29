add_library(io
    src/results_layout.cpp
    src/traj_io.cpp
)

target_include_directories(io
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Eigen3 REQUIRED NO_MODULE)
target_link_libraries(io
    PUBLIC config
    PUBLIC Eigen3::Eigen
)
