add_library(sh_prop
    src/quantum_me.cpp
    src/sh_utils.cpp
    src/cl_forces.cpp
    src/init_conds.cpp
)

target_include_directories(sh_prop
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Eigen3 REQUIRED NO_MODULE)
target_link_libraries(sh_prop
    PUBLIC config
    PUBLIC utils
    PUBLIC Eigen3::Eigen
)
