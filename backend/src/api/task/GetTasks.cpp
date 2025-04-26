#include "api/API.hpp"
#include "db/Database.hpp"
#include "models/Models.hpp"

#include <jwt-cpp/jwt.h>
#include <crow.h>

namespace projectify::API
{
    void GetTasks(const crow::request& req, crow::response& res)
    {
        const auto requestData = crow::json::load(req.body);
        
        if(!requestData.has("projectID") || requestData["projectID"].t() != crow::json::type::Number)
        {
            res.code = crow::status::BAD_REQUEST;
            res.end("You need to provide a valid JSON containing name and an integer projectID");
            return;
        }

        const auto userID = std::stoi(jwt::decode(req.get_header_value("Authorization")).get_subject());
        const auto projectID = requestData["projectID"].i();

        const auto [result, tasks] = Database::GetProjectTasks(userID, projectID);

        crow::json::wvalue::list jsonTasks;

        switch(result)
        {
            case projectify::Database::Result::NOT_FOUND:
                res.code = crow::status::NOT_FOUND;
                res.end("Couldn't find requested user or project");
                break;

            case projectify::Database::Result::SUCCESS:
                jsonTasks.reserve(tasks.size());

                for(const auto& task: tasks)
                    jsonTasks.emplace_back(task.Serialize());

                res.code = crow::status::OK;
                res.end(crow::json::wvalue{jsonTasks}.dump());
                break;

            default:
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end("The server encountered an unexpected error");
        }
    }
}