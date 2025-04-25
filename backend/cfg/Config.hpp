#pragma once

#include "utils/Utils.hpp"

#include <string>
#include <string_view>

namespace projectify::Config
{
    inline const auto PORT = std::stoi(projectify::Utils::GetEnv("PORT", "8000"));

    inline const std::string DB_NAME = projectify::Utils::GetEnv("POSTGRES_DB", "projectify-db");
    inline const std::string DB_USER = projectify::Utils::GetEnv("POSTGRES_USER", "username");
    inline const std::string DB_PASSWORD = projectify::Utils::GetEnv("POSTGRES_PASSWORD", "password");
    inline const auto DB_PORT = std::stoi(projectify::Utils::GetEnv("POSTGRES_PORT", "5432"));
    inline const std::string DB_HOST = projectify::Utils::GetEnv("POSTGRES_HOST", "localhost");

    inline const std::string DB_CONNECTION_STRING =
        std::format("dbname={} user={} password={} host={} port={}", DB_NAME, DB_USER, DB_PASSWORD, DB_HOST, DB_PORT);
}
