add_executable(main
    main.cpp
)

find_package(yaml-cpp REQUIRED)
target_link_libraries(main PRIVATE
    sh_prop
    config
    postproc
    utils
    io
    yaml-cpp::yaml-cpp
)

target_compile_options(main PRIVATE -O3)