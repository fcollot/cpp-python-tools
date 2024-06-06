# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/pyncppConfig_qt.cmake"
    DESTINATION "${PYNCPP_SHARE_SUBDIR}"
    COMPONENT Development
    )

foreach(qt_version ${qt_versions})

    pyncpp_wrap_package_config(Qt${qt_version} ${qt_version} PySide6 "Qt")

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/Qt${qt_version}Config.cmake"
        DESTINATION "${PYNCPP_SHARE_SUBDIR}"
        COMPONENT Development
        )

endforeach()
