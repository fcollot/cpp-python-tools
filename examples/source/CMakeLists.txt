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

project(pyncpp_examples VERSION "${PYNCPP_VERSION}")

################################################################################
# Dependencies
################################################################################

find_package(pyncpp REQUIRED
    OPTIONAL_COMPONENTS qt5 qt6
    )

set(qt_versions)

if(pyncpp_qt5_FOUND)
    list(APPEND qt_versions 5)
endif()

if(pyncpp_qt6_FOUND)
    list(APPEND qt_versions 6)
endif()

file(RELATIVE_PATH relative_lib_dir "/${pyncpp_UTILS_SUBDIR}" "/${pyncpp_LIBRARY_SUBDIR}")

if(APPLE)
    set(rpath "@executable_path/${relative_lib_dir}")
elseif(LINUX)
    set(rpath "\$ORIGIN/${relative_lib_dir}")
endif()

################################################################################
# Subdirectories
################################################################################

if(qt_versions)
    add_subdirectory(qt_application)
endif()
