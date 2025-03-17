# we need to bump minimal cmake version to 3.29 to enable CMP0156
cmake_minimum_required(VERSION 3.28)

cmake_policy(SET CMP0156 NEW)

project(spargel)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CTest)
include(AddSpargel)

##------------------
## System Detection
##------------------

if(${CMAKE_SYSTEM_NAME} STREQUAL Android)
    set(SPARGEL_IS_ANDROID YES CACHE BOOL "")
else()
    set(SPARGEL_IS_ANDROID NO CACHE BOOL "")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    set(SPARGEL_IS_MACOS YES CACHE BOOL "")
else()
    set(SPARGEL_IS_MACOS NO CACHE BOOL "")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL Emscripten)
    set(SPARGEL_IS_EMSCRIPTEN YES CACHE BOOL "")
else()
    set(SPARGEL_IS_EMSCRIPTEN NO CACHE BOOL "")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    set(SPARGEL_IS_LINUX YES CACHE BOOL "")
else()
    set(SPARGEL_IS_LINUX NO CACHE BOOL "")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    set(SPARGEL_IS_WINDOWS YES CACHE BOOL "")
else()
    set(SPARGEL_IS_WINDOWS NO CACHE BOOL "")
endif()

##---------
## Options
##---------

include(SpargelOptions)

##--------------
## Dependencies
##--------------

include(SpargelDependencies)

##----------------
## Static Analysis
##----------------

include(SpargelStaticAnalysis)

##------
## Misc
##------

if (SPARGEL_IS_ANDROID)
    set_target_properties(${SPARGEL_ANDROID_TARGET} PROPERTIES OUTPUT_NAME spargeldemo)
endif ()

##---------
## Sources
##---------

add_subdirectory(sample)
add_subdirectory(source)
