#include "api/API.hpp"
#include "db/Database.hpp"

#include <jwt-cpp/jwt.h>
#include <crow.h>

namespace projectify::API
{
    void DeleteProject(const crow::request& req, crow::response& res)
    {
        const auto requestData = crow::json::load(req.body);

        if(!requestData || !requestData.has("ID") || requestData["ID"].t() != crow::json::type::Number)
        {
            res.code = crow::status::BAD_REQUEST;
            res.end("You need to provide a valid JSON containing name");
            return;
        }

        const auto userID = std::stoi(jwt::decode(req.get_header_value("Authorization")).get_subject());
        const auto projectID = requestData["ID"].i();

        const auto result = Database::DeleteProject(userID, projectID);

        switch(result)
        {
            case projectify::Database::Result::NOT_FOUND:
                res.code = crow::status::NOT_FOUND;
                res.end("Couldn't find requested user or project");
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
