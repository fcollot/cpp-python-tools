# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

file(GLOB_RECURSE python_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.py"
    )

foreach(file ${python_files})
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${file}"
        "${CMAKE_CURRENT_BINARY_DIR}/${file}"
        @ONLY
        )
endforeach()

add_custom_target(pyncpp_python_api ALL
    COMMAND ${CMAKE_COMMAND} -E env
    "PYNCPP_PYTHONHOME=${pyncpp_PYTHON_DIR}"
    $<TARGET_FILE:pyncpp_executable> -m pip install "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM
    )
