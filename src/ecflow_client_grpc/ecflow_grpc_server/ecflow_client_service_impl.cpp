#include "ecflow_client_service_impl.h"

#include <ecflow_client.h>

#include <spdlog/spdlog.h>

EcflowClientServiceImpl::EcflowClientServiceImpl() {

}

::grpc::Status EcflowClientServiceImpl::CollectStatusRecords(
    ::grpc::ServerContext *context,
    const ::ecflow_client::StatusRequest *request,
    ::ecflow_client::StatusRecordsResponse *response) {

    spdlog::info("[{0}/{1}] receive request...", request->owner(), request->repo());

    response->set_owner(request->owner());
    response->set_repo(request->repo());

    EcflowUtil::EcflowClient client{request->host(), request->port()};
    client.sync();
    auto records = client.statusRecords();

    auto status_map = response->mutable_status_map();

    for(auto & record: records){
        (*status_map)[record.path_] = record.status_;
    }

    return grpc::Status::OK;
}

::grpc::Status
EcflowClientServiceImpl::CollectStatus(
    ::grpc::ServerContext *context,
    const ::ecflow_client::StatusRequest *request,
    ::ecflow_client::StatusResponse *response) {

    response->set_owner(request->owner());
    response->set_repo(request->repo());

    EcflowUtil::EcflowClient client{request->host(), request->port()};
    client.sync();
    auto bunch = client.bunch();

    response->set_status(bunch->toJsonString());

    return grpc::Status::OK;
}
