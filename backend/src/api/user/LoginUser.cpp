#include "api/API.hpp"
#include "db/Database.hpp"
#include "utils/Utils.hpp"

#include <crow.h>
#include <spdlog/spdlog.h>

namespace projectify::API
{
    void LoginUser(const crow::request& req, crow::response& res)
    {
        const auto requestData = crow::json::load(req.body);

        if(!requestData || !requestData.has("username") || !requestData.has("password"))
        {
            res.code = crow::status::BAD_REQUEST;
            res.end("You need to provide a valid JSON containing username and password");
            return;
        }

        const std::string_view username = requestData["username"].s().begin();
        const std::string_view password = requestData["password"].s().begin();

        const auto [result, user] = projectify::Database::GetUserByCredentials(username, password);

        switch(result)
        {
            case projectify::Database::Result::INVALID_CREDENTIALS:
                res.code = crow::status::NOT_FOUND;
                res.end("Account not found");
                break;

            case projectify::Database::Result::SUCCESS:
                res.code = crow::status::OK;
                res.set_header("Authorization", Utils::CreateJwt(user.value().ID));
                res.end(user.value().Serialize().dump());
                break;

            default:
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end("The server encountered an unexpected error");
                break;
        }
    }
}
