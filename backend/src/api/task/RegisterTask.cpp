#include "api/API.hpp"
#include "db/Database.hpp"
#include "models/Models.hpp"

#include <jwt-cpp/jwt.h>
#include <spdlog/spdlog.h>

namespace projectify::API
{
    void RegisterTask(const crow::request& req, crow::response& res)
    {
        spdlog::info("{}", req.body);
        const auto requestData = crow::json::load(req.body);
        
        if(!requestData || !requestData.has("name") || !requestData.has("projectID") ||
            requestData["projectID"].t() != crow::json::type::Number)
        {
            res.code = crow::status::BAD_REQUEST;
            res.end("You need to provide a valid JSON containing name and an integer projectID");
            return;
        }
        
        const auto userID = std::stoi(jwt::decode(req.get_header_value("Authorization")).get_subject());
        
        const std::string_view taskName = requestData["name"].s().begin();
        const auto taskProjectID = requestData["projectID"].i();
        
        if(!Models::Task::Validate(taskName))
        {
            res.code = crow::status::BAD_REQUEST;
            res.end("Task name invalid");
            return;
        }

        const auto [result, id] = Database::RegisterTask(userID, taskProjectID, taskName);

        switch(result)
        {
            case Database::Result::NOT_FOUND:
                res.code = crow::status::NOT_FOUND;
                res.end("Passed user or project not found");
                break;

            case Database::Result::ALREADY_PRESENT:
                res.code = crow::status::CONFLICT;
                res.end("This task is already present");
                break;

            case Database::Result::SUCCESS:
                res.code = crow::status::CREATED;
                res.end();
                break;

            default:
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end("The server encountered an unexpected error");
        }
    }
}
