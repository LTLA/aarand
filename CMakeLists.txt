cmake_minimum_required(VERSION 3.14)

project(aarand
    VERSION 1.0.0
    DESCRIPTION "Aaron's distribution functions"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(aarand INTERFACE)

target_include_directories(aarand INTERFACE include/)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif()
endif()
