#pragma once

#include "utils/Utils.hpp"

#include <string>
#include <string_view>

namespace projectify::Config
{
    inline const auto PORT = std::stoi(Utils::GetEnv("PORT", "8000"));

    inline const std::string DB_NAME = Utils::GetEnv("POSTGRES_DB", "projectify-db");
    inline const std::string DB_USER = Utils::GetEnv("POSTGRES_USER", "username");
    inline const std::string DB_PASSWORD = Utils::GetEnv("POSTGRES_PASSWORD", "password");
    inline const auto DB_PORT = std::stoi(Utils::GetEnv("POSTGRES_PORT", "5432"));
    inline const std::string DB_HOST = Utils::GetEnv("POSTGRES_HOST", "localhost");
    inline const std::string DB_SSL = Utils::GetEnv("POSTGRES_SSL", "disable");

    inline const std::string DB_CONNECTION_STRING =
        std::format("dbname={} user={} password={} host={} port={} sslmode={}", DB_NAME, DB_USER, DB_PASSWORD, DB_HOST, DB_PORT, DB_SSL);

    inline const auto REQUESTS_PER_MINUTE = std::stoi(Utils::GetEnv("REQUESTS_PER_MINUTE", "15"));
    inline const auto TIME_WINDOW = std::chrono::minutes(1);

    inline const std::regex USERNAME_REGEX(R"(^(?=[a-zA-Z])[a-zA-Z0-9]{7,64}$)");
    inline const std::regex PASSWORD_REGEX(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[-_!@#$%^&*]).{8,128}$)");

    inline const std::regex PROJECT_TASK_URL_NAME_REGEX(R"(^(?=[a-zA-Z])[a-zA-Z0-9 _\-.,!?@#$%^&*].{5,63}$)");

    inline const std::string JWT_SECRET = Utils::GetEnv("JWT_SECRET", "jwtSecret");
    inline const auto JWT_DURATION = std::chrono::seconds(std::stoi(Utils::GetEnv("JWT_DURATION", "3600")));
}
