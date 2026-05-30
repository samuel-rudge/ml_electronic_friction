add_library(config
    src/config.cpp
)

target_include_directories(config
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_directories(config
    PUBLIC utils
)