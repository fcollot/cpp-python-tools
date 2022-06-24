# Copyright (c) 2022 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

include(ExternalProject)

if(WIN32)
    set(_module_path windows)
else()
    set(_module_path unix)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${_module_path}" ${CMAKE_MODULE_PATH})

include(add_project)

add_project()
