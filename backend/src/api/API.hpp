#pragma once

#include <crow.h>

namespace projectify::API
{
    void RegisterUser(const crow::request& req, crow::response& res);
    void LoginUser(const crow::request& req, crow::response& res);

    void RegisterProject(const crow::request& req, crow::response& res);
    void GetProjects(const crow::request& req, crow::response& res);
    void DeleteProject(const crow::request& req, crow::response& res);

    void RegisterTask(const crow::request& req, crow::response& res);
    void GetTasks(const crow::request& req, crow::response& res);
    void ToggleTaskStatus(const crow::request& req, crow::response& res);
    void DeleteTask(const crow::request& req, crow::response& res);

    void RegisterLink(const crow::request& req, crow::response& res);
    void GetLinks(const crow::request& req, crow::response& res);
    void DeleteLink(const crow::request& req, crow::response& res);
}
