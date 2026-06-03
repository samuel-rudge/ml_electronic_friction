add_library(sh_prop
    src/traj_prop.cpp
    src/sh_utils.cpp
    src/cl_forces.cpp
    src/init_conds.cpp
    src/traj_workers.cpp
)

target_include_directories(sh_prop
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Eigen3 REQUIRED NO_MODULE)
find_package(OpenMP REQUIRED)
if (OpenMP_CXX_FOUND)
    target_link_libraries(sh_prop PUBLIC OpenMP::OpenMP_CXX)
endif()
target_link_libraries(sh_prop
    PUBLIC config
    PUBLIC utils
    PUBLIC Eigen3::Eigen
    PUBLIC io
)
