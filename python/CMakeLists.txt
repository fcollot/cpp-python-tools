# Copyright (c) 2023-2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

################################################################################
# Settings
################################################################################

set(PYNCPP_PYTHON_VERSION_MAJOR 3 CACHE STRING "Python major version")
set(PYNCPP_PYTHON_VERSION_MINOR 10 CACHE STRING "Python minor version")
set(PYNCPP_PYTHON_VERSION_PATCH 10 CACHE STRING "Python patch version")

set(PYNCPP_PYTHON_SHORT_VERSION "${PYNCPP_PYTHON_VERSION_MAJOR}.${PYNCPP_PYTHON_VERSION_MINOR}")
set(PYNCPP_PYTHON_SHORT_VERSION ${PYNCPP_PYTHON_SHORT_VERSION} PARENT_SCOPE)
set(PYNCPP_PYTHON_VERSION "${PYNCPP_PYTHON_SHORT_VERSION}.${PYNCPP_PYTHON_VERSION_PATCH}")
set(PYNCPP_PYTHON_VERSION ${PYNCPP_PYTHON_VERSION} PARENT_SCOPE)

if(WIN32)
    set(install_subdir "python${PYNCPP_PYTHON_VERSION_MAJOR}${PYNCPP_PYTHON_VERSION_MINOR}")
else()
    set(install_subdir "lib/python${PYNCPP_PYTHON_SHORT_VERSION}")
endif()

string(CONCAT install_subdir_text
    "Where to install the embedded Python interpreter when packaging the application"
    " (relative to the package root)"
    )

set(PYNCPP_PYTHON_INSTALL_SUBDIR "${install_subdir}" CACHE PATH ${install_subdir_text})

set(build_dir_text
    "Where to install the embedded Python interpreter when building the application"
    )

set(PYNCPP_PYTHON_SUBDIR "${install_subdir}" CACHE PATH ${build_dir_text})

set(prefix "${CMAKE_CURRENT_BINARY_DIR}")

################################################################################
# Platform-specific
################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/hash.cmake"

if(WIN32)
    include("${CMAKE_CURRENT_SOURCE_DIR}/windows.cmake")
else()
    include("${CMAKE_CURRENT_SOURCE_DIR}/unix.cmake")
endif()

################################################################################
# Config module
################################################################################

foreach(config ${CMAKE_CONFIGURATION_TYPES} ${CMAKE_BUILD_TYPE})

    string(TOUPPER ${config} CONFIG)

    configure_file("config_module.cmake.in"
        "pyncppConfig_python-${config}.cmake"
        @ONLY
        )

    install(
        "${CMAKE_CURRENT_BINARY_DIR}/pyncppConfig_python-${config}.cmake"
        CONFIGURATIONS ${config}
        DESTINATION "${PYNCPP_SHARE_SUBDIR}"
        COMPONENT Config
        RENAME "pyncppConfig_python.cmake"
        )

endforeach()

add_custom_target(pyncpp_python_config ALL
    COMMAND ${CMAKE_COMMAND}
    -D "CMAKE_INSTALL_PREFIX:PATH=${PROJECT_BINARY_DIR}"
    -D "CMAKE_INSTALL_CONFIG_NAME:STRING=$<CONFIG>"
    -D "CMAKE_INSTALL_COMPONENT:STRING=Config"
    -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake"
    COMPONENT Development
    )
