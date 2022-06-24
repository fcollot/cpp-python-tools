# Copyright (c) 2022 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

cmake_policy(SET CMP0011 NEW) # Policy PUSH/POP in included scripts

function(_create_package_config_files destination)
    configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/PythonConfig.cmake.in" "${destination}/PythonConfig.cmake"
        INSTALL_PREFIX "${PYTHON_PREFIX}"
        INSTALL_DESTINATION "${destination}"
        PATH_VARS PYTHON_SOURCE_DIR PYTHON_BINARY_DIR
        )

    write_basic_package_version_file("${destination}/PythonConfigVersion.cmake"
        VERSION "${PYNCPP_REQUIRED_PYTHON_VERSION}"
        COMPATIBILITY SameMinorVersion
        )
endfunction()

_create_package_config_files(${PYTHON_PREFIX})
_create_package_config_files(${_CMAKE_FIND_PACKAGE_REDIRECTS_DIR})

find_package(Python REQUIRED
    COMPONENTS Interpreter
    PATHS ${PYTHON_PREFIX}
    NO_DEFAULT_PATHS
    )

include(create_pth_file)

create_pth_file(${Python_EXECUTABLE}
    PATHS ${Python_STDLIB} ${Python_STDARCH}
    )
