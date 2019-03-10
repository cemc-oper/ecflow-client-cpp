#include <ecflow_client.grpc.pb.h>
#include <CLIUtils/CLI11.hpp>

#include <grpcpp/grpcpp.h>
#include <iostream>

int main(int argc, char** argv){
    CLI::App app{"A gRPC client for ecflow"};

    std::string rpc_target;

    app.add_option("--rpc-target", rpc_target, "RPC target")->required();

    CLI11_PARSE(app, argc, argv)

    grpc::ChannelArguments args;
    args.SetCompressionAlgorithm(GRPC_COMPRESS_GZIP);

    auto stub_ = ecflow_client::EcflowClientService::NewStub(
        grpc::CreateCustomChannel(
            rpc_target,
            grpc::InsecureChannelCredentials(),args));

    ecflow_client::StatusRequest request;
    request.set_host("10.40.143.18");
    request.set_port("31071");
    request.set_owner("nwp_xp");
    request.set_repo("nwpc_pd_bk");

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