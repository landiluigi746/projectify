#pragma once

#include <crow.h>

namespace projectify::API
{
    void RegisterUser(const crow::request& req, crow::response& res);
    void LoginUser(const crow::request& req, crow::response& res);
}
