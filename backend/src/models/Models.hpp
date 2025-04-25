#pragma once

#include <crow/json.h>
#include <string>

namespace projectify::Models
{
    struct User
    {
        int ID;
        std::string username;
        std::string passwordHash;

        static bool Validate(std::string_view username, std::string_view password);
        crow::json::wvalue Serialize() const;
    };
}
