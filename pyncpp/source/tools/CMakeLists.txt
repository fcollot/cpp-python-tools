# Copyright (c) 2023 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

#add_subdirectory(console)

set(sources
    pyncpp/__init__.py
    pyncpp/tkconsole.py
    setup.py
    )

add_custom_target(pyncpp_tools ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/setup.py" "${CMAKE_CURRENT_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/pyncpp" "${CMAKE_CURRENT_BINARY_DIR}/pyncpp"
    COMMAND ${PYNCPP_PYTHON_EXECUTABLE} -m pip install "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS ${sources}
    SOURCES ${sources}
    VERBATIM
    )
