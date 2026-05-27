cmake_minimum_required(VERSION 3.17)
project(ML_ELECTRONIC_FRICTION LANGUAGES CXX)

# -------------------------------
#          Compiler Flags
# -------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_subdirectory(source)

# -------------------------------
#         Include yaml-cpp
# -------------------------------

find_package(yaml-cpp REQUIRED)
# set(YAML_CPP_DIR "$ENV{HOME}/local/yaml-cpp")
# include_directories(${YAML_CPP_DIR}/include)
# link_directories(${YAML_CPP_DIR}/lib)

# -------------------------------
#         Add directories
# -------------------------------

# add_subdirectory(source)
# add_subdirectory(results)
# add_subdirectory(data)
# add_subdirectory(config)
# add_subdirectory(scripts)
# add_subdirectory(tests)

target_compile_options(main_harmonic PRIVATE -O3)
