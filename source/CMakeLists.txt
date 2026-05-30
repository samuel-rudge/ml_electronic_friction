add_subdirectory(utils)
add_subdirectory(config)
add_subdirectory(io)
add_subdirectory(sh_prop)

add_executable(main_sh
    main_sh.cpp
)

find_package(yaml-cpp REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
target_link_libraries(main_sh PRIVATE
    utils
    config
    io
    sh_prop
    yaml-cpp::yaml-cpp
    Eigen3::Eigen
    )
