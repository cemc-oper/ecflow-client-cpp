#include "storer.h"

#include <sw/redis++/redis++.h>
#include <spdlog/spdlog.h>
#include <chrono>

using namespace sw::redis;
using namespace std::chrono_literals;

namespace ecflow_watchman {

RedisStorer::RedisStorer(
        std::string redis_host, int redis_port, std::string password, int db):
        redis_host_{std::move(redis_host)},
        redis_port_{redis_port},
        password_{std::move(password)},
        db_{db} {
}

RedisStorer::~RedisStorer() {

}

void RedisStorer::create() {
    ConnectionOptions connection_options;
    connection_options.host = redis_host_;
    connection_options.port = redis_port_;
    connection_options.password = password_;   // Optional. No password by default.
    connection_options.db = db_;

    connection_options.socket_timeout = 1s;

    try {
        client_ = std::make_unique<Redis>(connection_options);
    } catch (const IoError &err) {
        spdlog::error("[redis] IoError in create(): {}", err.what());
    } catch (const Error &err) {
        spdlog::error("[redis] Error in create(): {}", err.what());
        throw;
    }
}

void RedisStorer::save(const std::string &key, const std::string &value) {
    try {
        client_->set(key, value);
    }catch (const TimeoutError &err) {
        spdlog::error("[redis] TimeoutError for {}: {}", key, err.what());
    } catch (const ClosedError &err) {
        spdlog::error("[redis] ClosedError for {}: {}", key,  err.what());
//        tryToCreate();
    } catch (const IoError &err) {
        spdlog::error("[redis] IoError for {}: {}", key,  err.what());
//        tryToCreate();
    } catch (const Error &err) {
        spdlog::error("[redis] Error for {}: {}", key, err.what());
    } catch (const std::exception &err) {
        spdlog::error("[redis] std::exception for {}: {}", key, err.what());
    }
}

void RedisStorer::tryToCreate() {
    ConnectionOptions connection_options;
    connection_options.host = redis_host_;
    connection_options.port = redis_port_;
    connection_options.password = password_;   // Optional. No password by default.
    connection_options.db = db_;

    connection_options.socket_timeout = 1s;

    try {
        client_ = std::make_unique<Redis>(connection_options);
    } catch (const IoError &err) {
        spdlog::error("[redis] IoError in create(): {}", err.what());
    } catch (const Error &err) {
        spdlog::error("[redis] Error in create(): {}", err.what());
    }
}

} // namespace ecflow_watchman