#pragma once

#include <ecflow_client/ecflow_client.grpc.pb.h>

#include <grpcpp/grpcpp.h>


class EcflowClientServiceImpl final : public ::ecflow_client::EcflowClientService::Service {
public:
    EcflowClientServiceImpl();

    ::grpc::Status CollectStatusRecords(
        ::grpc::ServerContext *context,
        const ::ecflow_client::StatusRequest *request,
        ::ecflow_client::StatusRecordsResponse *response) override;

    ::grpc::Status CollectStatus(
        ::grpc::ServerContext *context,
        const ::ecflow_client::StatusRequest *request,
        ::ecflow_client::StatusResponse *response) override;

    ::grpc::Status CollectNode(
        ::grpc::ServerContext *context,
        const ::ecflow_client::NodeRequest *request,
        ::ecflow_client::NodeResponse *response);

};

