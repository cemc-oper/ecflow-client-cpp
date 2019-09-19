#include <ecflow_client/ecflow_client.grpc.pb.h>
#include <CLIUtils/CLI11.hpp>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include <grpcpp/grpcpp.h>
#include <iostream>

int main(int argc, char **argv) {
    CLI::App app{"A gRPC client for ecflow"};

    std::string rpc_target;
    std::string host;
    std::string port;
    std::string owner;
    std::string repo;
    std::string path;

    app.add_option("--rpc-target", rpc_target, "RPC target")->required();
    app.add_option("--host", host, "host")->required();
    app.add_option("--port", port, "port")->required();
    app.add_option("--owner", owner, "owner")->required();
    app.add_option("--repo", repo, "host")->required();
    app.add_option("--path", path, "path")->required();

    CLI11_PARSE(app, argc, argv)

    grpc::ChannelArguments args;
    args.SetCompressionAlgorithm(GRPC_COMPRESS_GZIP);

    auto stub_ = ecflow_client::EcflowClientService::NewStub(
        grpc::CreateCustomChannel(
            rpc_target,
            grpc::InsecureChannelCredentials(), args));

    ecflow_client::NodeRequest request;
    request.set_host(host);
    request.set_port(port);
    request.set_owner(owner);
    request.set_repo(repo);
    request.set_path(path);

    ecflow_client::NodeResponse response;
    grpc::ClientContext context;
    context.set_compression_algorithm(GRPC_COMPRESS_DEFLATE);

    spdlog::info("[{0}/{1}] get node {2}...", owner, repo, path);
    grpc::Status status = stub_->CollectNode(&context, request, &response);
    spdlog::info("[{0}/{1}] get node {2}...done", owner, repo, path);

    if (status.ok()) {
        if (response.response_status().has_error()) {
            spdlog::warn("[{0}/{1}] get records...failed: {2}", owner, repo, response.response_status().error_string());
        } else {
            const auto &node_json_string = response.node();
            auto node_json = nlohmann::json::parse(node_json_string);
            std::cout << node_json.dump(2) << std::endl;
        }
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }

    return 0;
}