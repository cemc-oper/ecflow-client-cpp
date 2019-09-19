
if (NOT ECFLOW_BUILD_DIR OR NOT ECFLOW_SOURCE_DIR)
    message(FATAL_ERROR "Please set ECFLOW_BUILD_DIR and ECFLOW_SOURCE_DIR")
endif ()

add_library(Ecflow INTERFACE)

target_include_directories(Ecflow INTERFACE
    ${ECFLOW_SOURCE_DIR}/ACore/src
    ${ECFLOW_SOURCE_DIR}/ANattr/src
    ${ECFLOW_SOURCE_DIR}/ANode/src
    ${ECFLOW_SOURCE_DIR}/Base/src
    ${ECFLOW_SOURCE_DIR}/Base/src/cts
    ${ECFLOW_SOURCE_DIR}/Base/src/stc
    ${ECFLOW_SOURCE_DIR}/CSim/src
    ${ECFLOW_SOURCE_DIR}/Client/src
    )

target_link_libraries(Ecflow INTERFACE
    ${ECFLOW_BUILD_DIR}/Client/liblibclient.a
    ${ECFLOW_BUILD_DIR}/Base/libbase.a
    ${ECFLOW_BUILD_DIR}/CSim/liblibsimu.a
    ${ECFLOW_BUILD_DIR}/ANode/libnode.a
    ${ECFLOW_BUILD_DIR}/ANattr/libnodeattr.a
    ${ECFLOW_BUILD_DIR}/ACore/libcore.a
    )

add_library(Ecflow::Ecflow ALIAS Ecflow)