cmake_minimum_required(VERSION 3.8)
project(twamp)

set(CMAKE_C_STANDARD 11)

set(TWAMP_ALLOC_SOURCES twamp_alloc.c)
add_library(twamp_alloc ${TWAMP_ALLOC_SOURCES})

set(TWAMP_UTILS_SOURCES twamp_utils.c)
add_library(twamp_utils ${TWAMP_UTILS_SOURCES})

set(TWAMP_LITE_UNAUTHENTICATED_SOURCES twamp_lite_unauthenticated.c)
add_library(twamp_lite_unauthenticated ${TWAMP_LITE_UNAUTHENTICATED_SOURCES})

set(SOURCE_FILES main.c )
add_executable(twamp ${SOURCE_FILES})#3-party libraries

#3-party libraries
set(GLOBAL_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH})
include(CMakeLists_ExternalProjects.txt)