# Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

cmake_policy(SET CMP0011 NEW) # Policy PUSH/POP in included scripts
cmake_policy(SET CMP0048 NEW) # Project command manages version variables
cmake_policy(SET CMP0057 NEW) # IN_LIST operator
cmake_policy(SET CMP0068 NEW) # RPATH settings on macOS do not affect install_name

################################################################################
# Project
################################################################################

project(pyncpp VERSION "${PYNCPP_VERSION}")

################################################################################
# Dependencies
################################################################################

set(NO_PYNCPP_TARGETS TRUE)
find_package(pyncpp REQUIRED)

################################################################################
# Subdirectories
################################################################################

add_subdirectory(config)
add_subdirectory(cpp_api)
add_subdirectory(executable)
add_subdirectory(python_api)
