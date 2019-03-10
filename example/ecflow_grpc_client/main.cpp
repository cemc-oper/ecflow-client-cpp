#include <ecflow_client.grpc.pb.h>
#include <CLIUtils/CLI11.hpp>

#include <grpcpp/grpcpp.h>
#include <iostream>

int main(int argc, char** argv){
    CLI::App app{"A gRPC client for ecflow"};

    std::string rpc_target;
    std::string host;
    std::string port;
    std::string owner;
    std::string repo;

    app.add_option("--rpc-target", rpc_target, "RPC target")->required();
    app.add_option("--host", host, "host")->required();
    app.add_option("--port", port, "port")->required();
    app.add_option("--owner", owner, "owner")->required();
    app.add_option("--repo", repo, "host")->required();

    CLI11_PARSE(app, argc, argv)

    grpc::ChannelArguments args;
    args.SetCompressionAlgorithm(GRPC_COMPRESS_GZIP);

    auto stub_ = ecflow_client::EcflowClientService::NewStub(
        grpc::CreateCustomChannel(
            rpc_target,
            grpc::InsecureChannelCredentials(),args));

    ecflow_client::StatusRequest request;
    request.set_host(host);
    request.set_port(port);
    request.set_owner(owner);
    request.set_repo(repo);

    ecflow_client::StatusRecordsResponse response;
    grpc::ClientContext context;
    context.set_compression_algorithm(GRPC_COMPRESS_DEFLATE);
    grpc::Status status = stub_->CollectStatusRecords(&context, request, &response);

    if(status.ok()){
        const auto &status_map = response.status_map();
        for(auto &s : status_map){
            std::cout<<s.first<<": "<<s.second<<std::endl;
        }
    } else {
        std::cout<<status.error_code()<<": "<<status.error_message()<<std::endl;
    }

    return 0;
}