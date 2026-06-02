enable_testing()

add_executable(runTests
    test_init_conds.cpp
)

find_package(yaml-cpp REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
target_link_libraries(runTests
    PRIVATE gtest
    PRIVATE gtest_main
    pthread
    PRIVATE sh_prop
    PRIVATE config
    PUBLIC Eigen3::Eigen
    PUBLIC yaml-cpp::yaml-cpp
)

include(GoogleTest)
gtest_discover_tests(runTests)
