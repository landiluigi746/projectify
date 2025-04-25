#include "api/API.hpp"
#include "db/Database.hpp"
#include "models/Models.hpp"

#include <jwt-cpp/jwt.h>
#include <crow.h>

namespace projectify::API
{
    void GetProjects(const crow::request& req, crow::response& res)
    {
        const auto userID = std::stoi(jwt::decode(req.get_header_value("Authorization")).get_subject());
        const auto [result, projects] = Database::GetUserProjects(userID);

        crow::json::wvalue::list jsonProjects;

        switch(result)
        {
            case projectify::Database::Result::NOT_FOUND:
                res.code = crow::status::NOT_FOUND;
                res.end("Couldn't find requested user");
                break;

            case projectify::Database::Result::SUCCESS:
                jsonProjects.reserve(projects.size());

                for(const auto& project: projects)
                    jsonProjects.emplace_back(project.Serialize());

                res.code = crow::status::OK;
                res.end(crow::json::wvalue{jsonProjects}.dump());
                break;

            default:
                res.code = crow::status::INTERNAL_SERVER_ERROR;
                res.end("The server encountered an unexpected error");
        }
    }
}
