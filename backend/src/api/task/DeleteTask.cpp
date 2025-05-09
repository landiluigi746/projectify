#include "api/API.hpp"
#include "db/Database.hpp"
#include "models/Models.hpp"

#include <jwt-cpp/jwt.h>

namespace projectify::API
{
    void DeleteTask(const crow::request& req, crow::response& res)
    {
        const auto requestData = crow::json::load(req.body);

        if(!requestData.has("projectID") || requestData["projectID"].t() != crow::json::type::Number ||
            !requestData.has("taskID") || requestData["taskID"].t() != crow::json::type::Number)
        {
            res.code = crow::status::BAD_REQUEST;
            res.end("You need to provide a valid JSON containing name and an integer projectID and an integer taskID");
            return;
        }

        const auto userID = std::stoi(jwt::decode(req.get_header_value("Authorization")).get_subject());
        const auto projectID = requestData["projectID"].i();
        const auto taskID = requestData["taskID"].i();

        const Database::Result result = Database::DeleteTask(userID, projectID, taskID);

        switch(result)
        {
            case projectify::Database::Result::NOT_FOUND:
                res.code = crow::status::NOT_FOUND;
                res.end("Couldn't find requested user/project/task");
                break;

            case projectify::Database::Result::SUCCESS:
                res.code = crow::status::OK;
                res.end();
                break;

            default:
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end("The server encountered an unexpected error");
        }
    }
}
