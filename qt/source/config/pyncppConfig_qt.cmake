# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

foreach(_version 5 6)
    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/Qt${_version}Config.cmake")
        set(Qt${_version}_DIR "${CMAKE_CURRENT_LIST_DIR}")
        set(pyncpp_qt${_version}_FOUND TRUE)
    endif()
endforeach()
