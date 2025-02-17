cmake_minimum_required(VERSION 3.8)
project(TaskGraph)

set(CMAKE_TOOLCHAIN_FILE "${PWD}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(benchmark_DIR "${PWD}/vcpkg/packages/benchmark_x64-linux/share/benchmark/")

find_package(benchmark CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS unit_test_framework graph)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

add_executable(${PROJECT_NAME} main.cpp)

add_executable(runUnitTests unittests/test_example.cpp)
target_include_directories(runUnitTests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(runUnitTests PRIVATE Boost::unit_test_framework)

add_executable(benchmark benchmark/benchmark.cpp)
target_link_libraries(benchmark PRIVATE benchmark::benchmark Boost::graph)
