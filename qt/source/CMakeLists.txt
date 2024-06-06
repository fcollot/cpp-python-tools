# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

cmake_policy(SET CMP0011 NEW) # Policy PUSH/POP in included scripts
cmake_policy(SET CMP0048 NEW) # Project command manages version variables
cmake_policy(SET CMP0057 NEW) # IN_LIST operator
cmake_policy(SET CMP0068 NEW) # RPATH settings on macOS do not affect install_name

################################################################################
# Project
################################################################################

project(pyncpp_qt VERSION "${PYNCPP_VERSION}")

################################################################################
# Dependencies
################################################################################

find_package(pyncpp REQUIRED)

set(qt_versions)

if(PYNCPP_QT5)
    list(APPEND qt_versions 5)
endif()

if(PYNCPP_QT6)
    list(APPEND qt_versions 6)
endif()

################################################################################
# Subdirectories
################################################################################

add_subdirectory(config)
add_subdirectory(python_api)
add_subdirectory(cpp_api)
