# Copyright (c) 2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

set(target_prefix ${PROJECT_NAME}_cpp_api)

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
    qt.h
    console.h
    conversion/qobject.h
    )

set(sources
    console.cpp
    conversion/qobject.cpp
    )

################################################################################
# Library
################################################################################

foreach(qt_version ${qt_versions})
    add_library(${target_prefix}_${qt_version} SHARED
        ${headers}
        ${sources}
        )
endforeach()

################################################################################
# Compile definitions
################################################################################

foreach(qt_version ${qt_versions})
    if(qt_version EQUAL 5)
        set(shiboken_package "shiboken2")
    else()
        set(shiboken_package "shiboken6")
    endif()

    target_compile_definitions(${target_prefix}_${qt_version} PUBLIC
        PYNCPP_QT_VERSION=${qt_version}
        SHIBOKEN_PACKAGE="${shiboken_package}"
        )
endforeach()

################################################################################
# Includes
################################################################################

#foreach(qt_version ${qt_versions})
#    target_include_directories(${target_prefix}_${qt_version}
#        PUBLIC
#        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
#        )
#endforeach()

################################################################################
# Link
################################################################################

foreach(qt_version ${qt_versions})
    target_link_libraries(${target_prefix}_${qt_version} PRIVATE
        ${pyncpp_LIBRARY}
        Qt${qt_version}::Core
        Qt${qt_version}::Widgets
        )
endforeach()

################################################################################
# Install/Export
################################################################################

foreach(qt_version ${qt_versions})
    install(TARGETS ${target_prefix}_${qt_version}
        EXPORT ${target_prefix}_${qt_version}_export

        RUNTIME
        DESTINATION "${pyncpp_RUNTIME_SUBDIR}"
        COMPONENT Runtime

        LIBRARY
        DESTINATION "${pyncpp_LIBRARY_SUBDIR}"
        COMPONENT Runtime

        ARCHIVE
        DESTINATION "${pyncpp_ARCHIVE_SUBDIR}"
        )

    install(EXPORT ${target_prefix}_${qt_version}_export
        DESTINATION "${pyncpp_SHARE_SUBDIR}"
        )
endforeach()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
    DESTINATION "${pyncpp_INCLUDE_SUBDIR}/pyncpp/qt"
    FILES_MATCHING PATTERN "*.h"
    PATTERN "CMakeLists.txt" EXCLUDE
    )
