# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

foreach(PYNCPP_QT_VERSION ${qt_versions})

    if(PYNCPP_QT_VERSION EQUAL 5)
        set(PYNCPP_PYSIDE_VERSION 2)
    else()
        set(PYNCPP_PYSIDE_VERSION 6)
    endif()

    file(GLOB_RECURSE python_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.py"
        )

    foreach(file ${python_files})
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${file}"
            "${CMAKE_CURRENT_BINARY_DIR}/qt${PYNCPP_QT_VERSION}/${file}"
            @ONLY
            )
    endforeach()

    add_custom_target(${PROJECT_NAME}${PYNCPP_QT_VERSION}_python_api ALL
        COMMAND ${pyncpp_EXECUTABLE} -m pip install PySide${PYNCPP_PYSIDE_VERSION}
        COMMAND ${pyncpp_EXECUTABLE} -m pip install "${CMAKE_CURRENT_BINARY_DIR}/qt${PYNCPP_QT_VERSION}"
        VERBATIM
        )

endforeach()
