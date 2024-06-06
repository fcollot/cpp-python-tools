# Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

foreach(PYNCPP_QT_VERSION ${qt_versions})

    set(target qt${PYNCPP_QT_VERSION}_application)

    ############################################################################
    # Dependencies
    ############################################################################

    if(PYNCPP_QT_VERSION EQUAL 5)
        set(PYNCPP_PYSIDE_VERSION 2)
    else()
        set(PYNCPP_PYSIDE_VERSION 6)
    endif()

    find_package(Qt${PYNCPP_QT_VERSION} REQUIRED COMPONENTS Core Widgets)

    ############################################################################
    # Executable
    ############################################################################

    add_executable(${target}
        main.cpp
        )

    set(rpath ${CMAKE_INSTALL_RPATH} ${Qt6_RPATHS})

    set_target_properties(${target} PROPERTIES
        INSTALL_RPATH "${rpath}"
        BUILD_WITH_INSTALL_RPATH TRUE
        )

    target_compile_definitions(${target} PUBLIC
        PYNCPP_QT_VERSION=${PYNCPP_QT_VERSION}
        )

    ############################################################################
    # Python
    ############################################################################

    set(subdir "pyncpp_examples/qt")

    file(GLOB_RECURSE python_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}"
        "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/*.py"
        )

    foreach(file ${python_files})
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/${file}"
            "${CMAKE_CURRENT_BINARY_DIR}/qt${PYNCPP_QT_VERSION}/${subdir}${PYNCPP_QT_VERSION}/${file}"
            @ONLY
            )
    endforeach()

    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/setup.py"
        "${CMAKE_CURRENT_BINARY_DIR}/qt${PYNCPP_QT_VERSION}/setup.py"
        @ONLY
        )

    add_custom_target(${target}_python ALL
        COMMAND ${pyncpp_EXECUTABLE} -m pip install "${CMAKE_CURRENT_BINARY_DIR}/qt${PYNCPP_QT_VERSION}"
        VERBATIM
        )

    ############################################################################
    # Link
    ############################################################################

    target_link_libraries(${target} PUBLIC
        ${pyncpp_CPP_API_LIBRARY}
        Qt${PYNCPP_QT_VERSION}::Core
        Qt${PYNCPP_QT_VERSION}::Widgets
        )

    ############################################################################
    # Install
    ############################################################################

    install(TARGETS ${target}
        RUNTIME
        DESTINATION "${pyncpp_EXAMPLES_SUBDIR}"
        )

endforeach()
