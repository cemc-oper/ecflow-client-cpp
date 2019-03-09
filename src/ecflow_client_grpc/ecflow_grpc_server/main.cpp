#include "ecflow_client_service_impl.h"

#include <iostream>

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    EcflowClientServiceImpl service;
    grpc::ServerBuilder builder;

    builder.SetDefaultCompressionAlgorithm(GRPC_COMPRESS_GZIP);
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout<<"server listening on "<<server_address<<std::endl;

    server->Wait();
}

int main(int argc, char** argv){
    RunServer();

    return 0;
}