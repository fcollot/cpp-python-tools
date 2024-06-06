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

file(RELATIVE_PATH relative_lib_dir "/${pyncpp_UTILS_SUBDIR}" "/${pyncpp_LIBRARY_SUBDIR}")

if(APPLE)
    set(rpath "@executable_path/${relative_lib_dir}")
elseif(LINUX)
    set(rpath "\$ORIGIN/${relative_lib_dir}")
endif()

set_target_properties(pyncpp_executable PROPERTIES
    OUTPUT_NAME pyncpp
    INSTALL_RPATH ${rpath}
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
    DESTINATION "${PYNCPP_UTILS_SUBDIR}"
    )

install(EXPORT pyncpp_export_executable
    DESTINATION "${PYNCPP_SHARE_SUBDIR}"
    )
