# Copyright (c) 2022 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

################################################################################
# Generate SWIG runtime header
################################################################################

if(PYNCPP_SWIG_SUPPORT)
    set(SWIG_RUNTIME_HEADER_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/swig)
    set(SWIG_RUNTIME_HEADER ${SWIG_RUNTIME_HEADER_DIRECTORY}/swig_runtime.h)

    if(NOT EXISTS ${SWIG_RUNTIME_HEADER})
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E make_directory ${SWIG_RUNTIME_HEADER_DIRECTORY}
            COMMAND ${SWIG_EXECUTABLE}
            "-python"
            "-c++"
            "-external-runtime" ${SWIG_RUNTIME_HEADER}
            )
    endif()
endif()

################################################################################
# Sources
################################################################################

set(PYNCPP_HEADERS
    export.h
    pyncpp.h
    error/base_exception.h
    error/error.h
    error/error_handling.h
    error/exception_thrower.h
    error/exception_traceback.h
    error/exception_types.h
    external/cpython.h
    external/cpython_call.h
    manager/manager.h
    )

set(PYNCPP_SOURCES
    error/base_exception.cpp
    error/error_handling.cpp
    error/exception_thrower.cpp
    error/exception_traceback.cpp
    error/exception_types.cpp
    manager/manager.cpp
    )

################################################################################
# Library
################################################################################

add_library(pyncpp SHARED
    ${PYNCPP_HEADERS}
    ${PYNCPP_SOURCES}
    ${SWIG_RUNTIME_HEADER}
    )

target_compile_definitions(pyncpp
    PUBLIC
    "PYNCPP_QT5_SUPPORT=$<BOOL:PYNCPP_QT5_SUPPORT>"
    "PYNCPP_SWIG_SUPPORT=$<BOOL:PYNCPP_SWIG_SUPPORT>"
    )

################################################################################
# Includes
################################################################################

target_include_directories(pyncpp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/error
    ${CMAKE_CURRENT_SOURCE_DIR}/external
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${SWIG_RUNTIME_HEADER_DIRECTORY}>
    "$<BUILD_INTERFACE:${Python_INCLUDE_DIRS}>"
    $<INSTALL_INTERFACE:include/pyncpp>
    )

################################################################################
# Link
################################################################################

target_link_libraries(pyncpp PRIVATE
    Python_LIBRARY
    )

if(PYNCPP_QT5_SUPPORT)
    target_link_libraries(pyncpp PRIVATE
        Qt5::Core
        Qt5::Widgets
        )
endif()

################################################################################
# Install/Export
################################################################################

install(TARGETS pyncpp EXPORT pyncpp LIBRARY DESTINATION lib)
install(FILES ${PYNCPP_HEADERS} ${SWIG_RUNTIME_HEADER} DESTINATION include/pyncpp)
