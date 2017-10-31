cmake_minimum_required(VERSION 3.8)
project(twamp)

set(CMAKE_C_STANDARD 11)

set(TWAMP_ALLOC_SOURCES twamp_alloc.c)
#add_library(twamp_alloc ${TWAMP_ALLOC_SOURCES})

set(TWAMP_UTILS_SOURCES twamp_utils.c)
#add_library(twamp_utils ${TWAMP_UTILS_SOURCES})

set(TWAMP_LITE_UNAUTHENTICATED_SOURCES twamp_lite_unauthenticated.c)
#add_library(twamp_lite_unauthenticated ${TWAMP_LITE_UNAUTHENTICATED_SOURCES})

add_library(twamp ${TWAMP_ALLOC_SOURCES} ${TWAMP_UTILS_SOURCES} ${TWAMP_LITE_UNAUTHENTICATED_SOURCES})

#3-party libraries
set(GLOBAL_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH})
include(CMakeLists_ExternalProjects.txt)



set(SERVER_SOURCE_FILES server.c)
add_executable(twamp_server ${SERVER_SOURCE_FILES})
#target_link_libraries(twamp_server twamp_alloc twamp_utils twamp_lite_unauthenticated)
target_link_libraries(twamp_server twamp)
add_dependencies(twamp_server nanomsg_prj)
target_link_libraries(twamp_server nanomsg)

set(CLIENT_SOURCE_FILES client.c)
add_executable(twamp_client ${CLIENT_SOURCE_FILES})
#target_link_libraries(twamp_client twamp_alloc twamp_utils twamp_lite_unauthenticated)
target_link_libraries(twamp_client twamp)
add_dependencies(twamp_client nanomsg_prj)
target_link_libraries(twamp_client nanomsg)