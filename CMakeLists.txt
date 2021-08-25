cmake_minimum_required(VERSION 3.10)
project(wmon CXX Fortran)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(restclient-cpp REQUIRED)
set(restclient-cpp_INCLUDE_DIRS "${restclient-cpp_DIR}/../../../include")


add_library(wmon wmon.cpp wmon.hpp)
target_link_libraries(wmon restclient-cpp)
target_include_directories(wmon PUBLIC ${restclient-cpp_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})


add_executable(wmon_test wmon_test.cpp)
target_link_libraries(wmon_test wmon)

add_library(wmon_c wmon_c.cc)
target_link_libraries(wmon_c wmon)

add_library(wmon_f wmon.F90)
target_link_libraries(wmon_f PUBLIC wmon_c)

add_executable(wmon_test_f wmon_test.F90)
target_link_libraries(wmon_test_f wmon_f)
