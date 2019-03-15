
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set_target_properties(
    gRPC::grpc++
    PROPERTIES IMPORTED_GLOBAL TRUE
)