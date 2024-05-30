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

set(PYNCPP_EXAMPLES_VERSION "${PYNCPP_VERSION_MAJOR}.${PYNCPP_VERSION_MINOR}.${PYNCPP_VERSION_PATCH}")
project(pyncpp_examples VERSION "${PYNCPP_EXAMPLES_VERSION}")

################################################################################
# Settings
################################################################################

if(APPLE)
#    if(PYNCPP_EXAMPLES_FRAMEWORKS)
#        set(CMAKE_MACOSX_BUNDLE TRUE)
#    else()
        list(APPEND CMAKE_INSTALL_RPATH "@executable_path/../lib")
#    endif()
elseif(UNIX)
    list(APPEND CMAKE_INSTALL_RPATH "\${ORIGIN}/../lib")
endif()

################################################################################
# Dependencies
################################################################################

find_package(pyncpp REQUIRED
    OPTIONAL_COMPONENTS Qt5 Qt6
    )

set(qt_versions)

if(pyncpp_Qt5_FOUND)
    list(APPEND qt_versions 5)
endif()

if(pyncpp_Qt6_FOUND)
    list(APPEND qt_versions 6)
endif()

if(APPLE)
    foreach(qt_version ${qt_versions})
        find_package(Qt${qt_version} REQUIRED COMPONENTS Core Widgets)
        get_target_property(_qmake_executable Qt${qt_version}::qmake IMPORTED_LOCATION)
        get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
        find_program(MACDEPLOYQT{qt_version} macdeployqt HINTS "${_qt_bin_dir}")
    endforeach()
endif()

################################################################################
# Subdirectories
################################################################################

if(qt_versions)
    add_subdirectory(qt_application)
endif()
