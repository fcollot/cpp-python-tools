# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

set(subdir "pyncpp/qt")
set(commands)

file(GLOB_RECURSE python_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}"
    "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/*.py"
    )

foreach(qt_version ${qt_versions})
    if(qt_version EQUAL 5)
        set(PYSIDE_VERSION 2)
    else()
        set(PYSIDE_VERSION 6)
    endif()

    set(QT_VERSION ${qt_version})

    foreach(file ${python_files})
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/${file}"
            "${CMAKE_CURRENT_BINARY_DIR}/qt${qt_version}/${subdir}${qt_version}/${file}"
            @ONLY
            )
    endforeach()

    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/setup.py"
        "${CMAKE_CURRENT_BINARY_DIR}/qt${qt_version}/setup.py"
        @ONLY
        )

    list(APPEND commands
        COMMAND ${pyncpp_EXECUTABLE} -m pip install PySide${PYSIDE_VERSION}
        COMMAND ${pyncpp_EXECUTABLE} -m pip install "${CMAKE_CURRENT_BINARY_DIR}/qt${qt_version}"
        )

endforeach()

add_custom_target(${PROJECT_NAME}_python_api ALL
    ${commands}
    VERBATIM
    )
