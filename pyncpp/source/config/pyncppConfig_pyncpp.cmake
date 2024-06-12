# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

if(NOT NO_PYNCPP_TARGETS)
    include("${CMAKE_CURRENT_LIST_DIR}/pyncpp_export_cpp_api.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/pyncpp_export_executable.cmake")

    set(pyncpp_LIBRARY pyncpp_cpp_api)
    set(pyncpp_EXECUTABLE pyncpp_executable)
endif()

function(pyncpp_wrap_package_config package version python_package python_subdir)

    set(PACKAGE_NAME ${package})
    set(PACKAGE_VERSION ${version})
    set(BINARY_DIR "${pyncpp_PYTHON_SITE_DIR}/${python_package}/${python_subdir}")

    configure_package_config_file("${pyncpp_ROOT}/${pyncpp_SHARE_SUBDIR}/wrapConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/${package}Config.cmake"
        INSTALL_DESTINATION "."
        PATH_VARS BINARY_DIR
        )

endfunction()
