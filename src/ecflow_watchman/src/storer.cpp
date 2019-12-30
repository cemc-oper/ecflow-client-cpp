#include "storer.h"

#include <sw/redis++/redis++.h>
#include <chrono>

using namespace sw::redis;
using namespace std::chrono_literals;

namespace ecflow_watchman {

RedisStorer::RedisStorer(
        const std::string &redis_host, int redis_port, const std::string &password, int db):
        redis_host_{redis_host},
        redis_port_{redis_port},
        password_{password},
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

    client_ = std::make_unique<Redis>(connection_options);
}

void RedisStorer::save(const std::string &key, const std::string &value) {
    client_->set(key, value);
}

} // namespace ecflow_watchman