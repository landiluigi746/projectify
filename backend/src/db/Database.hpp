#pragma once

#include "models/Models.hpp"

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

    std::pair<Result, int> RegisterUser(std::string_view username, std::string_view password);
    std::pair<Result, std::optional<Models::User>> GetUserByCredentials(std::string_view username, std::string_view password);
}
