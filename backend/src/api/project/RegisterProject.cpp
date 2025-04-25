#include "api/API.hpp"
#include "db/Database.hpp"
#include "cfg/Config.hpp"
#include "models/Models.hpp"
#include "utils/Utils.hpp"

#include <jwt-cpp/jwt.h>
#include <crow.h>

namespace projectify::API
{
    void RegisterProject(const crow::request& req, crow::response& res)
    {
        const auto requestData = crow::json::load(req.body);

        if(!requestData || !requestData.has("name") || !requestData.has("description"))
        {
            res.code = crow::status::BAD_REQUEST;
            res.end("You need to provide a valid JSON containing name");
            return;
        }

        const auto userID = std::stoi(jwt::decode(req.get_header_value("Authorization")).get_subject());

        const std::string_view projectTitle = requestData["name"].s().begin();
        const std::string_view projectDescription = requestData["description"].s().begin();

        if(!Models::Project::Validate(projectTitle, projectDescription))
        {
            res.code = crow::status::BAD_REQUEST;
            res.end("Project name or description invalid");
            return;
        }

        const auto [result, id] = Database::RegisterProject(userID, projectTitle, projectDescription);

        switch(result)
        {
            case projectify::Database::Result::ALREADY_PRESENT:
                res.code = crow::status::CONFLICT;
                res.end("This project is already present");
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
