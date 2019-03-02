project(ecflow_client_cpp_test)

set(ECFLOW_BUILD_DIR /g3/wangdp/app/nwpc/ecmwf/ecflow/4.12/build-server)
set(ECFLOW_SOURCE_DIR /g3/wangdp/app/nwpc/ecmwf/ecflow/4.12/ecFlow-4.12.0-Source)

set(BOOST_ROOT /g3/wangdp/lib/cpp/boost/boost_1_53_0)

find_package(Boost
    REQUIRED
    COMPONENTS
    system
    filesystem
    date_time
    program_options
    serialization
    thread
    regex
    )

link_libraries(
    ${ECFLOW_BUILD_DIR}/Client/liblibclient.a
    ${ECFLOW_BUILD_DIR}/Base/libbase.a
    ${ECFLOW_BUILD_DIR}/CSim/liblibsimu.a
    ${ECFLOW_BUILD_DIR}/ANode/libnode.a
    ${ECFLOW_BUILD_DIR}/ANattr/libnodeattr.a
    ${ECFLOW_BUILD_DIR}/ACore/libcore.a
)

add_executable(ecflow_client_cpp_test
    main.cpp)

target_include_directories(ecflow_client_cpp_test PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${ECFLOW_SOURCE_DIR}/ACore/src
    ${ECFLOW_SOURCE_DIR}/ANattr/src
    ${ECFLOW_SOURCE_DIR}/ANode/src
    ${ECFLOW_SOURCE_DIR}/Base/src
    ${ECFLOW_SOURCE_DIR}/Base/src/cts
    ${ECFLOW_SOURCE_DIR}/Base/src/stc
    ${ECFLOW_SOURCE_DIR}/CSim/src
    ${ECFLOW_SOURCE_DIR}/Client/src
    )

target_link_libraries(ecflow_client_cpp_test PUBLIC
    Boost::system
    Boost::filesystem
    Boost::date_time
    Boost::program_options
    Boost::serialization
    Boost::thread
    Boost::regex
    )
