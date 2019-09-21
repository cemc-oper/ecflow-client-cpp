#include "ecflow_client_service_impl.h"

#include "ecflow_client/ecflow_client_standalone.h"

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

EcflowClientServiceImpl::EcflowClientServiceImpl() {

}

::grpc::Status EcflowClientServiceImpl::CollectStatusRecords(
    ::grpc::ServerContext *context,
    const ::ecflow_client::StatusRequest *request,
    ::ecflow_client::StatusRecordsResponse *response) {

    spdlog::info("[{0}/{1}] receive request...", request->owner(), request->repo());

    response->set_owner(request->owner());
    response->set_repo(request->repo());

    spdlog::info("[{0}/{1}] getting status from server...{2}:{3}",
                 request->owner(), request->repo(), request->host(), request->port());
    EcflowUtil::EcflowClient client{request->host(), request->port()};
    auto ret = client.sync();
    if (ret != 0) {
        response->mutable_response_status()->set_has_error(true);
        response->mutable_response_status()->set_error_string(client.errorMessage());
        return grpc::Status::OK;
    }

    auto records = client.statusRecords();
    spdlog::info("[{0}/{1}] getting status from server...done", request->owner(), request->repo());

    auto status_map = response->mutable_status_map();

    for (auto &record: records) {
        (*status_map)[record.path_] = record.status_;
    }

    spdlog::info("[{0}/{1}] CollectStatusRecords...done", request->owner(), request->repo());
    return grpc::Status::OK;
}

::grpc::Status
EcflowClientServiceImpl::CollectStatus(
    ::grpc::ServerContext *context,
    const ::ecflow_client::StatusRequest *request,
    ::ecflow_client::StatusResponse *response) {

    spdlog::info("[{0}/{1}] receive request...", request->owner(), request->repo());

    response->set_owner(request->owner());
    response->set_repo(request->repo());

    spdlog::info("[{0}/{1}] getting status from server...{2}:{3}",
                 request->owner(), request->repo(), request->host(), request->port());

    EcflowUtil::EcflowClient client{request->host(), request->port()};

    auto ret = client.sync();
    if (ret != 0) {
        response->mutable_response_status()->set_has_error(true);
        response->mutable_response_status()->set_error_string(client.errorMessage());
        return grpc::Status::OK;
    }
    spdlog::info("[{0}/{1}] getting status from server...done", request->owner(), request->repo());

    auto bunch = client.bunch();
    response->set_status(bunch->toJsonString());

    spdlog::info("[{0}/{1}] CollectStatus...done", request->owner(), request->repo());

    return grpc::Status::OK;
}

::grpc::Status
EcflowClientServiceImpl::CollectNode(
    ::grpc::ServerContext *context, const
::ecflow_client::NodeRequest *request,
    ::ecflow_client::NodeResponse *response) {

    spdlog::info("[{0}/{1}] receive node request [{2}:{3}]...",
                 request->owner(), request->repo(), request->host(), request->port());

    response->set_owner(request->owner());
    response->set_repo(request->repo());

    spdlog::info("[{0}/{1}] getting node from server [{2}]...",
                 request->owner(), request->repo(), request->path());

    EcflowUtil::EcflowClient client{request->host(), request->port()};

    auto ret = client.sync();
    if (ret != 0) {
        response->mutable_response_status()->set_has_error(true);
        response->mutable_response_status()->set_error_string(client.errorMessage());
        return grpc::Status::OK;
    }

    auto node = client.getWorkflowNode(request->path());
    if (!node) {
        response->mutable_response_status()->set_has_error(true);
        response->mutable_response_status()->set_error_string("node path doesn't exist.");
        spdlog::info("[{0}/{1}] getting node from server [{2}]...failed",
                     request->owner(), request->repo(), request->path());
        return grpc::Status::OK;
    }
    spdlog::info("[{0}/{1}] getting node from server [{2}]...done",
                 request->owner(), request->repo(), request->path());

    response->set_node(node->toJson().dump());

    return grpc::Status::OK;
}
