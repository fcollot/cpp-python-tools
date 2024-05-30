# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

################################################################################
# Config module
################################################################################

install(
    "${CMAKE_CURRENT_SOURCE_DIR}/config_module.cmake"
    DESTINATION "${PYNCPP_SHARE_SUBDIR}"
    COMPONENT Development
    RENAME "pyncppConfig_tools.cmake"
    )

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/config_wrapper.cmake.in"
    DESTINATION "${PYNCPP_SHARE_SUBDIR}"
    COMPONENT Development
    )
