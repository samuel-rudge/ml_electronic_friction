add_library(postproc
    src/postproc_utils.cpp
    src/postproc_main.cpp
)

target_include_directories(postproc
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Eigen3 REQUIRED NO_MODULE)
target_link_libraries(postproc
    PUBLIC config
    PUBLIC Eigen3::Eigen
    PUBLIC io
    PUBLIC utils
)
