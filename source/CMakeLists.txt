add_subdirectory(utils)
add_subdirectory(config)

add_executable(main_harmonic
    main_harmonic.cpp
)

find_package(yaml-cpp REQUIRED)
target_link_libraries(main_harmonic PRIVATE
    utils
    config
    yaml-cpp::yaml-cpp
    #    CONFIG_PATH="${CMAKE_SOURCE_DIR}/config/settings.yaml"
    )
