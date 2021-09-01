cmake_minimum_required(VERSION 3.10)
project(wmonf 
  LANGUAGES Fortran 
  VERSION 0.1)

include(GNUInstallDirs)
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/wmon" )
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/wmon" )
set(RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}" )
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}" )

find_package(wmon REQUIRED)

add_library(wmon_f wmon.F90)
target_link_libraries(wmon_f PUBLIC wmon_c)

#disable, not working with pgi
#add_executable(wmon_test_f wmon_test.F90)
#target_link_libraries(wmon_test_f wmon_f)

install(TARGETS wmon_f EXPORT wmonfTargets
  PUBLIC_HEADER DESTINATION ${INCLUDE_INSTALL_DIR}
  RUNTIME DESTINATION ${RUNTIME_INSTALL_DIR}
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
)

install(FILES ${CMAKE_BINARY_DIR}/wmon.mod DESTINATION ${CMAKE_INSTALL_PREFIX}/include/wmon)

#install(
#  FILES
#    ${CMAKE_CURRENT_BINARY_DIR}/wmonConfig.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/wmonConfigVersion.cmake
#  DESTINATION
#    ${CMAKE_INSTALL_PREFIX}/${CONFIG_INSTALL_DIR}
#)

# export targets for find_package config mode
#install(EXPORT wmonTargets DESTINATION ${CONFIG_INSTALL_DIR})

