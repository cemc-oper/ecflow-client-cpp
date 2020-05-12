#pragma once
#include <string>
#include <memory>

namespace sw {
namespace redis {
class Redis;
}
}

namespace ecflow_watchman {

class RedisStorer final {
public:
    RedisStorer(std::string redis_host, int redis_port, std::string password="", int db=0);
    ~RedisStorer();

    void create();

    void save(const std::string &key, const std::string &value);

private:
    void tryToCreate();

    std::string redis_host_;
    int redis_port_;
    std::string password_;
    int db_;

    std::unique_ptr<sw::redis::Redis> client_;
};

} // namespace ecflow_watchman