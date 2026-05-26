add_subdirectory(utils)

add_executable(main_harmonic
    main_harmonic.cpp
)

find_package(yaml-cpp REQUIRED)
target_link_libraries(main_harmonic PRIVATE utils yaml-cpp::yaml-cpp)
