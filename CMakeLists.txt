cmake_minimum_required(VERSION 3.11)

project("Bitonic sort" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCL REQUIRED)

add_executable(main main.cpp)

#target_include_directories(main PUBLIC "kernel")

target_link_libraries(main PRIVATE OpenCL::OpenCL)

target_compile_definitions(main PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

option(BUILD_TESTS "Build tests" ON)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()