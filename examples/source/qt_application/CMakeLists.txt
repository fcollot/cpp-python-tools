# Copyright (c) 2022-2024 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

foreach(qt_version ${qt_versions})

    set(target qt${qt_version}_application)

    ############################################################################
    # Executable
    ############################################################################

    add_executable(${target}
        main.cpp
        )

    file(RELATIVE_PATH python_home "${pyncpp_ROOT}/bin" "${pyncpp_PYTHON_DIR}")

    target_compile_definitions(${target} PUBLIC
        PYTHON_HOME="${python_home}"
        )

    set(rpath ${CMAKE_INSTALL_RPATH} ${Qt6_PATHS})

    set_target_properties(${target} PROPERTIES
        INSTALL_RPATH "${rpath}"
        )

    ############################################################################
    # Link
    ############################################################################

    target_link_libraries(${target} PUBLIC
        ${pyncpp_CPP_API_LIBRARY}
        Qt${qt_version}::Core
        Qt${qt_version}::Widgets
        )

    ############################################################################
    # Install
    ############################################################################

    add_custom_target(${target}_python ALL
        COMMAND ${pyncpp_EXECUTABLE} -m pip install "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM
        )

    #if(PYNCPP_EXAMPLES_FRAMEWORKS)
    #    install(TARGETS qt_application
    #        BUNDLE
    #        DESTINATION bin
    #        COMPONENT qt_application
    #        )

    #    set(_bundle_install_path "\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/bin/qt_application.app")

    #    install(CODE "
    #        execute_process(COMMAND ${MACDEPLOYQT_EXECUTABLE} \"${_bundle_install_path}\")
    #        include(BundleUtilities)
    #        fixup_bundle(\"${_bundle_install_path}\" \"\" \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/lib\")
    #        "
    #        COMPONENT qt_application
    #        )
    #else()
    install(TARGETS ${target}
        RUNTIME
        DESTINATION "bin"
        )
    #endif()

endforeach()
