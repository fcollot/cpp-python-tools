# Copyright (c) 2022-2023 IHU Liryc, Université de Bordeaux, Inria.
# License: BSD-3-Clause

################################################################################
# External project
################################################################################

ExternalProject_Add(pyncpp_python
    PREFIX "${prefix}"
    DOWNLOAD_DIR "${prefix}/download"
    SOURCE_DIR "${prefix}/source"
    BINARY_DIR "${prefix}/source"
    STAMP_DIR "${prefix}/stamp"
    TMP_DIR "${prefix}/tmp"
    URL "https://www.python.org/ftp/python/${PYNCPP_PYTHON_VERSION}/Python-${PYNCPP_PYTHON_VERSION}.tgz"
    URL_MD5 ${PYNCPP_PYTHON_UNIX_TGZ_${PYNCPP_PYTHON_VERSION_MAJOR}_${PYNCPP_PYTHON_VERSION_MINOR}_${PYNCPP_PYTHON_VERSION_PATCH}_MD5}
    CONFIGURE_COMMAND ""
    DOWNLOAD_COMMAND ""
    BUILD_COMMAND "" #${CMAKE_COMMAND} -E env "<SOURCE_DIR>/PCbuild/build.bat" $<$<CONFIG:Debug>:-d> $<$<CONFIG:Release>:--pgo>
    INSTALL_COMMAND ${CMAKE_COMMAND}
    --install "${CMAKE_CURRENT_BINARY_DIR}"
    --prefix "${PYNCPP_BINARY_DIR}"
    --config $<CONFIG>
    )

ExternalProject_Add_Step(pyncpp_python post_install
    DEPENDEES install
    COMMAND "${PYNCPP_BINARY_DIR}/${PYNCPP_PYTHON_SUBDIR}/python$<$<CONFIG:Debug>:_d>.exe" -m ensurepip --upgrade
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    "${PYNCPP_BINARY_DIR}/${PYNCPP_PYTHON_SUBDIR}/include"
    "${PROJECT_BINARY_DIR}/include/python${PYNCPP_PYTHON_SHORT_VERSION}"
    )

################################################################################
# Install
################################################################################

set(build_dir ${CMAKE_CURRENT_BINARY_DIR}/source/PCBuild/amd64)
set(source_dir ${CMAKE_CURRENT_BINARY_DIR}/source)

install(PROGRAMS
    "${build_dir}/pythonw$<$<CONFIG:Debug>:_d>.exe"
    "${build_dir}/python$<$<CONFIG:Debug>:_d>.exe"
    DESTINATION "${PYNCPP_PYTHON_SUBDIR}"
    COMPONENT Runtime
    )

set(runtime_files
    "${build_dir}/python${PYNCPP_PYTHON_VERSION_MAJOR}${PYNCPP_PYTHON_VERSION_MINOR}$<$<CONFIG:Debug>:_d>.dll"
    "${build_dir}/vcruntime140.dll"
    )

install(FILES ${runtime_files}
    DESTINATION "${PYNCPP_PYTHON_SUBDIR}"
    COMPONENT Runtime
    )

install(CODE "
    file(WRITE \"\${CMAKE_INSTALL_PREFIX}/@PYNCPP_PYTHON_SUBDIR@/python@PYNCPP_PYTHON_VERSION_MAJOR@@PYNCPP_PYTHON_VERSION_MINOR@$<$<CONFIG:Debug>:_d>._pth\"
        \".\\n\"
        \"Lib\\n\"
        \"DLLs\\n\"
        \"import site\"
        )
    "
    COMPONENT Runtime
    )

install(DIRECTORY "${source_dir}/Lib/"
    DESTINATION "${PYNCPP_PYTHON_SUBDIR}/Lib"
    COMPONENT Runtime
    PATTERN "*.pyc" EXCLUDE
    )

install(DIRECTORY "${build_dir}/"
    DESTINATION "${PYNCPP_PYTHON_SUBDIR}/DLLs"
    COMPONENT Runtime
    FILES_MATCHING
    PATTERN "*.dll"
    PATTERN "*.pyd"
    PATTERN "python*" EXCLUDE
    PATTERN "vcruntime*" EXCLUDE
    )

install(DIRECTORY "${build_dir}/"
    DESTINATION "${PYNCPP_PYTHON_SUBDIR}/libs"
    COMPONENT Development
    FILES_MATCHING
    PATTERN "python*.lib"
    )

install(DIRECTORY "${source_dir}/Include/"
    DESTINATION "${PYNCPP_PYTHON_SUBDIR}/include"
    COMPONENT Development
    )

install(FILES "${source_dir}/PC/pyconfig.h"
    DESTINATION "${PYNCPP_PYTHON_SUBDIR}/include"
    COMPONENT Development
    )

#configure_file("windows_install.cmake.in" "windows_install.cmake.tmp" @ONLY)

#file(GENERATE
#    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/windows_install-$<CONFIG>.cmake"
#    INPUT "${CMAKE_CURRENT_BINARY_DIR}/windows_install.cmake.tmp"
#    )

#install(CODE "
#    execute_process(COMMAND ${CMAKE_COMMAND}
#        -D \"CMAKE_INSTALL_PREFIX:PATH=\${CMAKE_INSTALL_PREFIX}/${PYNCPP_PYTHON_SUBDIR}\"
#        -D \"INSTALL_RUNTIME:BOOL=TRUE\"
#        -P \"${CMAKE_CURRENT_BINARY_DIR}/windows_install-$<CONFIG>.cmake\"
#        )
#    "
#    COMPONENT Runtime
#    )

#install(CODE "
#    execute_process(COMMAND ${CMAKE_COMMAND}
#        -D \"CMAKE_INSTALL_PREFIX:PATH=\${CMAKE_INSTALL_PREFIX}/${PYNCPP_PYTHON_SUBDIR}\"
#        -D \"INSTALL_DEVELOPMENT:BOOL=TRUE\"
#        -P \"${CMAKE_CURRENT_BINARY_DIR}/windows_install-$<CONFIG>.cmake\"
#        )
#    "
#    COMPONENT Development
#    )
