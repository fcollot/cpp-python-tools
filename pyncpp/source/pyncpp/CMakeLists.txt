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

add_executable(pyncpp
    ${headers}
    ${sources}
    )

set(compile_definitions
    PYTHON_HOME="${pyncpp_PYTHON_DIR}"
    )

if(PYNCPP_QT5_SUPPORT)
    list(APPEND compile_definitions PYNCPP_QT5_SUPPORT)
endif()

target_compile_definitions(pyncpp PUBLIC
    ${compile_definitions}
    )

################################################################################
# Includes
################################################################################

#target_include_directories(pyncpp
#    PRIVATE
#    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/pyncpp"
#    PUBLIC
#    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
#    "$<INSTALL_INTERFACE:include/pyncpp/cpp_api>"
#    )

################################################################################
# Link
################################################################################

target_link_libraries(pyncpp PUBLIC
    pyncpp_cpp_api
    )

################################################################################
# Install/Export
################################################################################

install(TARGETS pyncpp
    EXPORT pyncpp_exports

    RUNTIME
    DESTINATION "bin"
    COMPONENT Development
    )
