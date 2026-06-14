add_executable(main
    main.cpp
)

find_package(yaml-cpp REQUIRED)
find_package(OpenMP REQUIRED)
if (OpenMP_CXX_FOUND)
    target_link_libraries(main PUBLIC OpenMP::OpenMP_CXX)
endif()
target_link_libraries(main PRIVATE
    sh_prop
    config
    postproc
    utils
    io
    yaml-cpp::yaml-cpp
)


target_compile_options(main PRIVATE -O3)