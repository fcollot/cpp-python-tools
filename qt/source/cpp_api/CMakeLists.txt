# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

foreach(PYNCPP_QT_VERSION ${qt_versions})

    set(target ${PROJECT_NAME}${PYNCPP_QT_VERSION}_cpp_api)

    if(PYNCPP_QT_VERSION EQUAL 5)
        set(PYNCPP_SHIBOKEN_VERSION)
    else()
        set(PYNCPP_SHIBOKEN_VERSION 2)
    endif()

    ############################################################################
    # Dependencies
    ############################################################################

    find_package(Qt${PYNCPP_QT_VERSION} REQUIRED COMPONENTS Core)

    ############################################################################
    # Files
    ############################################################################

    set(headers
        qt.h
        conversion/qobject.h
        )

    set(sources
        conversion/qobject.cpp
        )

    set(files)

    foreach(file ${headers} ${sources})
        set(configured_file "${CMAKE_CURRENT_BINARY_DIR}/qt${PYNCPP_QT_VERSION}/${file}")
        list(APPEND files "${configured_file}")
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${file}"
            "${configured_file}"
            @ONLY
            )
    endforeach()

    ############################################################################
    # Library
    ############################################################################

    add_library(${target} SHARED
        ${files}
        )

    target_compile_definitions(${target} PUBLIC
        PYNCPP_QT_VERSION=${PYNCPP_QT_VERSION}
        )

    ############################################################################
    # Includes
    ############################################################################

    target_include_directories(${target}
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/qt${PYNCPP_QT_VERSION}>"
        "$<INSTALL_INTERFACE:include/pyncpp/qt${PYNCPP_QT_VERSION}>"
        )

    ############################################################################
    # Link
    ############################################################################

    target_link_libraries(${target} PUBLIC
        ${pyncpp_CPP_API_LIBRARY}
        Qt${PYNCPP_QT_VERSION}::Core
        )

    ############################################################################
    # Install/Export
    ############################################################################

    install(TARGETS ${target}
        EXPORT ${target}_export

        RUNTIME
        DESTINATION "${pyncpp_RUNTIME_SUBDIR}"
        COMPONENT Runtime

        LIBRARY
        DESTINATION "${pyncpp_LIBRARY_SUBDIR}"
        COMPONENT Runtime

        ARCHIVE
        DESTINATION "${pyncpp_ARCHIVE_SUBDIR}"
        )

    install(EXPORT ${target}_export
        DESTINATION "${PYNCPP_SHARE_SUBDIR}"
        )

    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/qt${PYNCPP_QT_VERSION}/"
        DESTINATION ""${pyncpp_INCLUDE_SUBDIR}"/pyncpp/qt${PYNCPP_QT_VERSION}"
        PATTERN "*.h"
        PATTERN "CMakeLists.txt" EXCLUDE
        )

endforeach()
