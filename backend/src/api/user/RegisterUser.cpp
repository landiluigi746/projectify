#include "api/API.hpp"
#include "db/Database.hpp"
#include "cfg/Config.hpp"
#include "models/Models.hpp"
#include "utils/Utils.hpp"

#include <crow.h>

namespace projectify::API
{
    void RegisterUser(const crow::request &req, crow::response &res)
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

        if(!Models::User::Validate(username, password))
        {
            res.code = crow::status::BAD_REQUEST;
            res.end("Username or password invalid");
            return;
        }

        const auto [result, id] = projectify::Database::RegisterUser(username, password);

        switch(result)
        {
            case projectify::Database::Result::ALREADY_PRESENT:
                res.code = crow::status::CONFLICT;
                res.end("This username is already registered");
                break;

            case projectify::Database::Result::SUCCESS:
                res.code = crow::status::CREATED;
                res.end();
                break;

            default:
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end("The server encountered an unexpected error");
        }
    }
}
