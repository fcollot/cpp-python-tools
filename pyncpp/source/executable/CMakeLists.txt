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

if(APPLE)
    set(rpath "@executable_path/../lib")
elseif(LINUX)
    set(rpath "\$ORIGIN/../lib")
endif()

set_target_properties(pyncpp_executable PROPERTIES
    OUTPUT_NAME pyncpp
    INSTALL_RPATH ${rpath}
    )

file(RELATIVE_PATH python_home "${pyncpp_ROOT}/bin" "${pyncpp_PYTHON_DIR}")

if(WIN32)
    set(os_name WINDOWS)
elseif(LINUX)
    set(os_name LINUX)
elseif(APPLE)
    set(os_name MACOS)
endif()

target_compile_definitions(pyncpp_executable PUBLIC
    PYTHON_HOME="${python_home}"
    OS_${os_name}
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
    EXPORT pyncpp_exports

    RUNTIME
    DESTINATION "bin"
    COMPONENT Development
    )
