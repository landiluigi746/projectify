#pragma once

#include <cstdint>
#include <tao/pq.hpp>

namespace projectify::Database
{
    enum class Result : uint8_t
    {
        SUCCESS,
        FAILED,
        ALREADY_PRESENT,
        NOT_FOUND,
        INVALID_CREDENTIALS,
    };

    using Connection = std::shared_ptr<tao::pq::connection>;

    std::shared_ptr<tao::pq::connection_pool>& GetConnectionPool();
    Result Init();
}
