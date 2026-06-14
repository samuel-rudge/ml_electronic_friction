add_library(utils
    src/math_utils.cpp
)

target_include_directories(utils
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Eigen3 REQUIRED NO_MODULE)
find_package(OpenMP REQUIRED)
if (OpenMP_CXX_FOUND)
    target_link_libraries(utils PUBLIC OpenMP::OpenMP_CXX)
endif()
target_link_libraries(utils
    PUBLIC Eigen3::Eigen
)
