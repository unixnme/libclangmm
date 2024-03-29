cmake_minimum_required(VERSION 2.8)

project(clangmm)

add_compile_options(-std=c++11 -Wall -Wextra -O0)

if(APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif()

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
  set(NOT_SUB_PROJECT 1)
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
find_package(LibClang REQUIRED)

add_subdirectory(src)

option(BUILD_TESTING ON)

if(${NOT_SUB_PROJECT})
  set(BUILD_TESTING ON)
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
