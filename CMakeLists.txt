cmake_minimum_required(VERSION 3.10)
project(wmon 
  LANGUAGES CXX
  VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/wmon" )
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/wmon" )
set(RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}" )
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}" )

find_package(restclient-cpp REQUIRED)
set(restclient-cpp_INCLUDE_DIRS "${restclient-cpp_DIR}/../../../include")

set(wmon_PUBLIC_HEADERS
  "wmon.hpp"
  "wmon_c.h"  
)

add_library(wmon wmon.cpp wmon.hpp)
target_link_libraries(wmon restclient-cpp)
target_include_directories(wmon PUBLIC ${restclient-cpp_INCLUDE_DIRS} $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<INSTALL_INTERFACE:include/wmon>)


add_executable(wmon_test wmon_test.cpp)
target_link_libraries(wmon_test wmon)

add_library(wmon_c wmon_c.cc)
target_link_libraries(wmon_c wmon)

set_property(TARGET wmon_c PROPERTY
  PUBLIC_HEADER ${wmon_PUBLIC_HEADERS})

include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_PREFIX}/${CONFIG_INSTALL_DIR}
  PATH_VARS
    INCLUDE_INSTALL_DIR
    CONFIG_INSTALL_DIR
    RUNTIME_INSTALL_DIR
    LIB_INSTALL_DIR
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/wmonConfigVersion.cmake"
  COMPATIBILITY
    SameMajorVersion
)

install(TARGETS wmon_c wmon EXPORT wmonTargets
  PUBLIC_HEADER DESTINATION ${INCLUDE_INSTALL_DIR}
  RUNTIME DESTINATION ${RUNTIME_INSTALL_DIR}
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/wmonConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/wmonConfigVersion.cmake
  DESTINATION
    ${CMAKE_INSTALL_PREFIX}/${CONFIG_INSTALL_DIR}
)

# export targets for find_package config mode
install(EXPORT wmonTargets DESTINATION ${CONFIG_INSTALL_DIR})

