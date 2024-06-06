# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

################################################################################
# Configuration
################################################################################

set(cmake_args
    -D "CMAKE_MINIMUM_REQUIRED_VERSION:STRING=${CMAKE_MINIMUM_REQUIRED_VERSION}"
    -D "CMAKE_BUILD_TYPE:PATH=${CMAKE_BUILD_TYPE}"
    -D "CMAKE_CXX_STANDARD:STRING=${CMAKE_CXX_STANDARD}"
    -D "CMAKE_CXX_STANDARD_REQUIRED:BOOL=${CMAKE_CXX_STANDARD_REQUIRED}"
    -D "CMAKE_MAKE_PROGRAM:PATH=${CMAKE_MAKE_PROGRAM}"
    -D "pyncpp_ROOT:PATH=${PYNCPP_ROOT}"
    -D "PYNCPP_VERSION:STRING=${PYNCPP_VERSION}"
    -D "PYNCPP_QT5:STRING=${PYNCPP_QT5}"
    -D "PYNCPP_QT6:STRING=${PYNCPP_QT6}"
    )

set(prefix "${CMAKE_CURRENT_BINARY_DIR}")

################################################################################
# External project
################################################################################

ExternalProject_Add(pyncpp_qt
    PREFIX "${prefix}"
    DOWNLOAD_DIR "${prefix}/download"
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source"
    BINARY_DIR "${prefix}/build"
    STAMP_DIR "${prefix}/stamp"
    TMP_DIR "${prefix}/tmp"
    DEPENDS pyncpp
    CMAKE_ARGS ${cmake_args}
    INSTALL_COMMAND ${CMAKE_COMMAND}
    --install "<BINARY_DIR>"
    --prefix "${PYNCPP_ROOT}"
    --config $<CONFIG>
    )

################################################################################
# Install
################################################################################

install(CODE "
    execute_process(COMMAND ${CMAKE_COMMAND}
        -D \"CMAKE_INSTALL_PREFIX:PATH=\${CMAKE_INSTALL_PREFIX}\"
        -D \"CMAKE_INSTALL_CONFIG_NAME:STRING=\$<CONFIG>\"
        -D \"CMAKE_INSTALL_COMPONENT:STRING=Runtime\"
        -P \"${prefix}/build/cmake_install.cmake\"
        )
    "
    COMPONENT Runtime
    )

install(CODE "
    execute_process(COMMAND ${CMAKE_COMMAND}
        -D \"CMAKE_INSTALL_PREFIX:PATH=\${CMAKE_INSTALL_PREFIX}\"
        -D \"CMAKE_INSTALL_CONFIG_NAME:STRING=\$<CONFIG>\"
        -P \"${prefix}/build/cmake_install.cmake\"
        )
    "
    )
