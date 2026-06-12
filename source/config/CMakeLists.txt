add_library(config
    src/config.cpp
    src/qu_ops.cpp
)

target_include_directories(config
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(config
    PUBLIC utils
)