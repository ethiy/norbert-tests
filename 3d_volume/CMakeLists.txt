cmake_minimum_required(VERSION 3.2)

project(
    "3d_volume"
    LANGUAGES CXX
)
include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup(TARGETS)

include_directories(BEFORE "${PROJECT_SOURCE_DIR}/src/include")

add_subdirectory(src/lib lib)
