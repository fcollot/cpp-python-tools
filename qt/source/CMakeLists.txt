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

set(PYNCPP_VERSION "${PYNCPP_VERSION_MAJOR}.${PYNCPP_VERSION_MINOR}.${PYNCPP_VERSION_PATCH}")
project(pyncpp_qt VERSION "${PYNCPP_VERSION}")

################################################################################
# Dependencies
################################################################################

find_package(pyncpp REQUIRED
    OPTIONAL_COMPONENTS Qt5 Qt6
    )

set(qt_versions)

if(pyncpp_Qt5_FOUND)
    list(APPEND qt_versions 5)

    add_custom_target(${PROJECT_NAME}_pyside2 ALL
        COMMAND ${pyncpp_EXECUTABLE} -m pip install PySide2
        )
endif()

if(pyncpp_Qt6_FOUND)
    list(APPEND qt_versions 6)

    add_custom_target(${PROJECT_NAME}_pyside6 ALL
        COMMAND ${pyncpp_EXECUTABLE} -m pip install PySide6
        )
endif()

################################################################################
# Config
################################################################################

pyncpp_wrap_package_config(Qt6 PySide6 Qt)

################################################################################
# Install
################################################################################



#set(PREFIX_DIR "${PROJECT_BINARY_DIR}")

#foreach(qt_version ${qt_versions})
#    configure_package_config_file("${CMAKE_CURRENT_LIST_DIR}/Qt${qt_version}Config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/Qt${qt_version}Config.cmake"
#        INSTALL_PREFIX "${PREFIX_DIR}"
#        INSTALL_DESTINATION "${PREFIX_DIR}/${PYNCPP_SHARE_SUBDIR}"
#        PATH_VARS PREFIX_DIR PYNCPP_PYTHON_DIR
#        )

#    write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/Qt${qt_version}ConfigVersion.cmake"
#        VERSION "@PROJECT_VERSION_MAJOR@.@PROJECT_VERSION_MINOR@.@PROJECT_VERSION_PATCH@"
#        COMPATIBILITY SameMinorVersion
#        )

#    install(FILES
#        "${CMAKE_CURRENT_BINARY_DIR}/Qt${qt_version}Config.cmake"
#        DESTINATION "${PYNCPP_SHARE_SUBDIR}"
#        COMPONENT Development
#        )

#    install(FILES
#        "${CMAKE_CURRENT_BINARY_DIR}/Qt${qt_version}ConfigVersion.cmake"
#        DESTINATION "${PYNCPP_SHARE_SUBDIR}"
#        COMPONENT Development
#        )
#endforeach()
