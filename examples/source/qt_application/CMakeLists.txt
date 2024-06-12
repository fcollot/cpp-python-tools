# Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

set(target_prefix ${PROJECT_NAME}_qt_application)

################################################################################
# Dependencies
################################################################################

foreach(qt_version ${qt_versions})
    find_package(Qt${qt_version} REQUIRED COMPONENTS Core Widgets)
endforeach()

################################################################################
# Files
################################################################################

set(headers
    test_button.h
    )

set(sources
    main.cpp
    test_button.cpp
    )

################################################################################
# Executable
################################################################################

foreach(qt_version ${qt_versions})
    add_executable(${target_prefix}_${qt_version}
        ${headers}
        ${sources}
        )
endforeach()

################################################################################
# Dependency loading
################################################################################

foreach(qt_version ${qt_versions})
    if(UNIX)
        set(rpaths)

        foreach(path ${Qt${qt_version}_PATHS})
            file(RELATIVE_PATH rpath "/${pyncpp_EXAMPLES_SUBDIR}" "/${path}")

            if(APPLE)
                set(rpath "@executable_path/${rpath}")
            else()
                set(rpath "\$ORIGIN/${rpath}")
            endif()

            list(APPEND rpaths "${rpath}")
        endforeach()

        set_target_properties(${target_prefix}_${qt_version} PROPERTIES
            OUTPUT_NAME qt${qt_version}_application
            INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${rpaths}"
            BUILD_WITH_INSTALL_RPATH TRUE
            )
    else()
    endif()
endforeach()

################################################################################
# Compile definitions
################################################################################

file(RELATIVE_PATH relative_python_dir "${pyncpp_ROOT}/${pyncpp_EXAMPLES_SUBDIR}" "/${pyncpp_PYTHON_DIR}")

foreach(qt_version ${qt_versions})
    target_compile_definitions(${target_prefix}_${qt_version} PUBLIC
        QT_VERSION_MAJOR="${qt_version}"
        PYTHON_HOME="${relative_python_dir}"
        PACKAGE_NAME="${target_prefix}_${qt_version}"
        )
endforeach()

################################################################################
# Link
################################################################################

foreach(qt_version ${qt_versions})
    target_link_libraries(${target_prefix}_${qt_version} PUBLIC
        ${pyncpp_LIBRARY}
        ${pyncpp_QT${qt_version}_LIBRARY}
        Qt${qt_version}::Core
        Qt${qt_version}::Widgets
        )
endforeach()

################################################################################
# Install
################################################################################

set(install_targets)

foreach(qt_version ${qt_versions})
    list(APPEND install_targets ${target_prefix}_${qt_version})
endforeach()

install(TARGETS ${install_targets}
    RUNTIME
    DESTINATION "${pyncpp_EXAMPLES_SUBDIR}"
    )

################################################################################
# Python
################################################################################

set(commands)

file(GLOB_RECURSE python_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/python"
    "${CMAKE_CURRENT_SOURCE_DIR}/python/*.py"
    )

foreach(qt_version ${qt_versions})
    if(qt_version EQUAL 5)
        set(PYSIDE_VERSION 2)
    else()
        set(PYSIDE_VERSION 6)
    endif()

    set(PACKAGE_NAME ${target_prefix}_${qt_version})

    foreach(file ${python_files})
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/python/${file}"
            "${CMAKE_CURRENT_BINARY_DIR}/qt${qt_version}/${target_prefix}_${qt_version}/${file}"
            @ONLY
            )
    endforeach()

    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/setup.py"
        "${CMAKE_CURRENT_BINARY_DIR}/qt${qt_version}/setup.py"
        @ONLY
        )

    list(APPEND commands COMMAND ${pyncpp_EXECUTABLE} -m pip
        install "${CMAKE_CURRENT_BINARY_DIR}/qt${qt_version}"
        -t "${PYNCPP_EXAMPLES_SITE_DIR}"
        --upgrade
        )
endforeach()

add_custom_target(${target_prefix}_python ALL
    ${commands}
    VERBATIM
    )
