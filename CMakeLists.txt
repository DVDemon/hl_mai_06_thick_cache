cmake_minimum_required(VERSION 3.2)

project(hl_mai_06_thick_cache C CXX)

SET (TARGET "hl_mai_06_thick_cache")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(Ignite REQUIRED)
find_package(Threads)
find_package(Java 1.8 REQUIRED)
find_package(JNI REQUIRED)

include_directories(SYSTEM ${IGNITE_INCLUDE_DIR} ${JNI_INCLUDE_DIRS})
#include_directories(../include)

add_executable(${TARGET} main.cpp)

target_link_libraries(${TARGET} ${IGNITE_LIB} ${IGNITE_JNI_LIB} ${IGNITE_BINARY_LIB} ${IGNITE_COMMON_LIB}
        ${CMAKE_THREAD_LIBS_INIT})
