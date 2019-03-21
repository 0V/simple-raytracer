cmake_minimum_required (VERSION 3.1)

project(raytracer)

# For debug
set(CMAKE_BUILD_TYPE Debug)

set(BUILD_TARGET "raytracer")

set(CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL, "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE, "-O4 -DNDEBUG")

file(GLOB "${BUILD_TARGET}_SOURCES" src/*.cc)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
    message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
  endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else ()
  message(FATAL_ERROR "Your C++ compiler does not support C++11.")
endif ()

include_directories("${INCLUDE_DIR}")

add_executable(${BUILD_TARGET} ${${BUILD_TARGET}_SOURCES})


