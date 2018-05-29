#
# Open World Manager
#

cmake_minimum_required(VERSION 3.2)

#
# Building in-tree is not allowed (we take care of your craziness).
#

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

#
# Project configuration
#

project(owman VERSION 0.0.1)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(OpenGL REQUIRED)
find_package(sdl2 REQUIRED)
find_package(glm REQUIRED)
find_package(unofficial-box2d REQUIRED)
find_package(GLEW REQUIRED)
#
# Compiler stuff
#
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(${owman_SOURCE_DIR}/src)

add_subdirectory(src)

#
# AOB
#

add_custom_target(
    owman_aob
    SOURCES
        LICENSE
)
