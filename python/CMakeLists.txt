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
    set(subdir "${PYNCPP_LIBRARY_SUBDIR}/python${PYNCPP_PYTHON_VERSION_MAJOR}${PYNCPP_PYTHON_VERSION_MINOR}")
elseif(APPLE AND PYNCPP_MACOS_BUNDLE)
    set(subdir "${PYNCPP_MACOS_BUNDLE_NAME}.app/Contents/Resources")
else()
    set(subdir "${PYNCPP_LIBRARY_SUBDIR}/python${PYNCPP_PYTHON_SHORT_VERSION}")
endif()

set(subdir_text
    "Path of the embedded Python interprete relative to the package root"
    )

set(PYNCPP_PYTHON_SUBDIR "${subdir}" CACHE PATH ${subdir_text})

set(PYNCPP_PYTHON_DIR "${PYNCPP_ROOT}/${PYNCPP_PYTHON_SUBDIR}")

set(prefix "${CMAKE_CURRENT_BINARY_DIR}")

################################################################################
# Platform-specific
################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/hash.cmake")

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

    configure_file("pyncppConfig_python.cmake.in"
        "pyncppConfig_python-${config}.cmake"
        @ONLY
        )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/pyncppConfig_python-${config}.cmake"
        CONFIGURATIONS ${config}
        DESTINATION "${PYNCPP_SHARE_SUBDIR}"
        COMPONENT Config
        RENAME pyncppConfig_python.cmake
        )

endforeach()

add_custom_target(pyncpp_python_config ALL
    COMMAND ${CMAKE_COMMAND}
    -D "CMAKE_INSTALL_PREFIX:PATH=${PYNCPP_ROOT}"
    -D "CMAKE_INSTALL_CONFIG_NAME:STRING=$<CONFIG>"
    -D "CMAKE_INSTALL_COMPONENT:STRING=Config"
    -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake"
    )
