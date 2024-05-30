# Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

cmake_minimum_required(VERSION 3.19)

cmake_policy(SET CMP0011 NEW) # Policy PUSH/POP in included scripts
cmake_policy(SET CMP0048 NEW) # Project command manages version variables
cmake_policy(SET CMP0057 NEW) # IN_LIST operator
cmake_policy(SET CMP0068 NEW) # RPATH settings on macOS do not affect install_name
cmake_policy(SET CMP0135 NEW) # ExternalProject_Add uses time of extraction for timestamps

include(CMakePackageConfigHelpers)
include(ExternalProject)

################################################################################
# Version
################################################################################

find_package(Git)
set(_success FALSE)

if(GIT_EXECUTABLE)
    execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --always
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE _git_describe
        )

    if (_git_describe MATCHES "^v\\.([0-9]+)\\.([0-9]+)(-([0-9]+))?.*$")
        set(PYNCPP_VERSION_MAJOR ${CMAKE_MATCH_1})
        set(PYNCPP_VERSION_MINOR ${CMAKE_MATCH_2})
        if(CMAKE_MATCH_4)
            set(PYNCPP_VERSION_PATCH ${CMAKE_MATCH_4})
        else()
            set(PYNCPP_VERSION_PATCH 0)
        endif()
        set(_success TRUE)
    endif()
endif()

if(_success)
    message(STATUS "Version number generated from git: ${PYNCPP_VERSION_MAJOR}.${PYNCPP_VERSION_MINOR}.${PYNCPP_VERSION_PATCH}")
else()
    set(PYNCPP_VERSION_MAJOR 0)
    set(PYNCPP_VERSION_MINOR 0)
    set(PYNCPP_VERSION_PATCH 0)
    message(WARNING "Cannot use git to generate a version number. Defaulting to 0.0.0")
endif()

################################################################################
# Project
################################################################################

set(PYNCPP_VERSION "${PYNCPP_VERSION_MAJOR}.${PYNCPP_VERSION_MINOR}.${PYNCPP_VERSION_PATCH}")
project(pyncpp VERSION "${PYNCPP_VERSION}")

################################################################################
# Settings
################################################################################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(PYNCPP_SHARE_SUBDIR "cmake")
else()
    set(PYNCPP_SHARE_SUBDIR "share/cmake/pyncpp")
endif()

get_property(GENERATOR_IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(NOT GENERATOR_IS_MULTI_CONFIG AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

option(PYNCPP_QT5 "Include Qt5 (using PySide2)" OFF)
option(PYNCPP_QT6 "Include Qt6 (using PySide6)" OFF)

option(PYNCPP_BUILD_EXAMPLES "Build example project" OFF)

################################################################################
# Subdirectories
################################################################################

add_subdirectory(python)
add_subdirectory(config)
add_subdirectory(pyncpp)

if(PYNCPP_QT5 OR PYNCPP_QT6)
    add_subdirectory(qt)
endif()

if(PYNCPP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
