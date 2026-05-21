cmake_minimum_required(VERSION 3.17)
project(SHHEOM LANGUAGES CXX)

# -------------------------------
#          Compiler Flags
# -------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# -------------------------------
#         Include yaml-cpp
# -------------------------------

set(YAML_CPP_DIR "$ENV{HOME}/local/yaml-cpp")
include_directories(${YAML_CPP_DIR}/include)
link_directories(${YAML_CPP_DIR}/lib)

# -------------------------------
#         Add directories
# -------------------------------

add_subdirectory(source)
add_subdirectory(results)
add_subdirectory(data)
add_subdirectory(config)
add_subdirectory(scripts)
add_subdirectory(tests)
