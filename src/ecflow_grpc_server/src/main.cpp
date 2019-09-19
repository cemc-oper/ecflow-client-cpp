#include "ecflow_client_service_impl.h"

#include <spdlog/spdlog.h>
#include <CLIUtils/CLI11.hpp>

void RunServer(const std::string &server_address) {
    EcflowClientServiceImpl service;
    grpc::ServerBuilder builder;

    builder.SetDefaultCompressionAlgorithm(GRPC_COMPRESS_GZIP);
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    spdlog::info("server listening on {0}", server_address);

    server->Wait();
}

int main(int argc, char **argv) {
    CLI::App app{"A gRPC server for ecflow"};

    std::string rpc_target;

    app.add_option("--rpc-target", rpc_target, "RPC target")->required();

    CLI11_PARSE(app, argc, argv)

    RunServer(rpc_target);

    return 0;
}