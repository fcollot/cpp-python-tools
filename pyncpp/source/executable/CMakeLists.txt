# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

################################################################################
# Files
################################################################################

set(headers
    )

set(sources
    main.cpp
    )

################################################################################
# Library
################################################################################

add_executable(pyncpp_executable
    ${headers}
    ${sources}
    )

################################################################################
# Target properties
################################################################################

if(UNIX)
    file(RELATIVE_PATH relative_lib_dir "/${pyncpp_UTILS_SUBDIR}" "/${pyncpp_LIBRARY_SUBDIR}")

    if(APPLE)
        set(rpath "@executable_path/${relative_lib_dir}")
    else()
        set(rpath "\$ORIGIN/${relative_lib_dir}")
    endif()

    set_target_properties(pyncpp_executable PROPERTIES
        INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${rpath}"
        )
endif()

set_target_properties(pyncpp_executable PROPERTIES
    OUTPUT_NAME pyncpp
    )

################################################################################
# Compile definitions
################################################################################

file(RELATIVE_PATH relative_python_dir "${pyncpp_ROOT}/${pyncpp_UTILS_SUBDIR}" "/${pyncpp_PYTHON_DIR}")

target_compile_definitions(pyncpp_executable PUBLIC
    PYTHON_HOME="${relative_python_dir}"
    )

################################################################################
# Link
################################################################################

target_link_libraries(pyncpp_executable PUBLIC
    pyncpp_cpp_api
    )

################################################################################
# Install/Export
################################################################################

install(TARGETS pyncpp_executable
    EXPORT pyncpp_export_executable

    RUNTIME
    DESTINATION "${pyncpp_UTILS_SUBDIR}"
    )

install(EXPORT pyncpp_export_executable
    DESTINATION "${pyncpp_SHARE_SUBDIR}"
    )
