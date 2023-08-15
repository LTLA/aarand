cmake_minimum_required(VERSION 3.24)

project(aarand
    VERSION 1.0.1
    DESCRIPTION "Aaron's random distribution functions"
    LANGUAGES CXX)

# Library
add_library(aarand INTERFACE)
add_library(ltla::aarand ALIAS aarand)

include(GNUInstallDirs)
target_include_directories(aarand INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ltla_aarand>)

target_compile_features(aarand INTERFACE cxx_std_17)

# Tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(AARAND_TESTS "" ON)
else()
    option(AARAND_TESTS "" OFF)
endif()
if(AARAND_TESTS)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif()
endif()

# Install
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ltla_aarand)

install(TARGETS aarand
    EXPORT aarandTargets)

install(EXPORT aarandTargets
    FILE ltla_aarandConfig.cmake
    NAMESPACE ltla::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ltla_aarand)
