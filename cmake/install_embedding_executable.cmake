# Copyright (c) 2022 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

function(PYNCPP_install_embedding_executable target)

    cmake_parse_arguments(PARSE_ARGV 1 "ARG"
        ""
        "DESTINATION;STDLIB_PATH"
        "EXTRA_PATHS"
        )

    if(NOT ARG_DESTINATION)
        message(FATAL_ERROR "Missing DESTINATION.")
    endif()

    if(NOT ARG_STDLIB_PATH)
        message(FATAL_ERROR "Missing STDLIB_PATH.")
    endif()

    get_target_property(is_bundle ${target} MACOSX_BUNDLE)

    set(code "
        set(CMAKE_MODULE_PATH \"${CMAKE_CURRENT_FUNCTION_LIST_DIR}\" \"\${CMAKE_MODULE_PATH}\")
        ")

    if(is_bundle)
        set(executable_path "\${CMAKE_INSTALL_PREFIX}/${ARG_DESTINATION}/$<TARGET_BUNDLE_DIR_NAME:${target}>/Content/MacOS/$<TARGET_FILE_NAME:${target}>")
        install(TARGETS ${target} BUNDLE DESTINATION ${ARG_DESTINATION})
    else()
        set(executable_path "\${CMAKE_INSTALL_PREFIX}/${ARG_DESTINATION}/$<TARGET_FILE_NAME:${target}>")
        install(TARGETS ${target} RUNTIME DESTINATION ${ARG_DESTINATION})
    endif()

    set(sys_paths
        "${STDLIB_PATH}"
        "${STDLIB_PATH}/lib-dynload"
        )

    foreach(path ${ARG_EXTRA_PATHS})
        list(APPEND sys_paths "\${CMAKE_INSTALL_PREFIX}/${path}")
    endforeach()

    string(APPEND code "
        include(create_path_config_file)
        PYNCPP_create_path_config_file(\"${executable_path}\" PATHS ${sys_paths})
        ")

    install(CODE "${code}")

endfunction()
