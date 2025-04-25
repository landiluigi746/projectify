#include "db/Database.hpp"
#include "utils/Utils.hpp"

#include <spdlog/spdlog.h>

namespace projectify::Database
{
    std::pair<Result, int> RegisterUser(std::string_view username, std::string_view password)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();
            const auto tr = conn->transaction();

            const auto res = tr->execute("register_user", username, Utils::HashString(password));
            tr->commit();

            if(res.empty())
                return std::make_pair(Result::ALREADY_PRESENT, -1);

            spdlog::debug("Database::RegisterUser() : Registered user with id {}", res[0][0].as<int>());
            return std::make_pair(Result::SUCCESS, res[0][0].as<int>());
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::RegisterUser() : {}", e.what());
            return std::make_pair(Result::FAILED, -1);
        }
    }

    std::pair<Result, std::optional<Models::User>> GetUserByCredentials(std::string_view username, std::string_view password)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();
            const auto res = conn->execute("get_user_credentials", username);

            if(res.empty())
                return std::make_pair(Result::INVALID_CREDENTIALS, std::nullopt);

            if(!Utils::CheckHashedString(password, res[0][2].as<std::string_view>()))
                return std::make_pair(Result::INVALID_CREDENTIALS, std::nullopt);

            return std::make_pair(Result::SUCCESS, Models::User{res[0][0].as<int>(), res[0][1].as<std::string>(), res[0][2].as<std::string>()});
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::GetUserByCredentials() : {}", e.what());
            return std::make_pair(Result::FAILED, std::nullopt);
        }
    }
}
