# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/pyncppConfig_pyncpp.cmake"
    DESTINATION "${pyncpp_SHARE_SUBDIR}"
    )

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/wrapConfig.cmake.in"
    DESTINATION "${pyncpp_SHARE_SUBDIR}"
    )
