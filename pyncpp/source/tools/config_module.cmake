# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

include("${CMAKE_CURRENT_LIST_DIR}/pyncpp_exports.cmake")

set(pyncpp_CPP_API_LIBRARY pyncpp_cpp_api)
set(pyncpp_EXECUTABLE pyncpp_executable)

function(pyncpp_wrap_package_config package python_package python_sub_dir)

    set(PACKAGE ${package})
    set(PACKAGE_BINARY_DIR)

    configure_file("${CMAKE_CURRENT_LIST_DIR}/config_wrapper.cmake.in"
        ${package}_config_wrapper.cmake.in
        @ONLY
        )

endfunction()
