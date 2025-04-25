#pragma once

#include <crow/json.h>
#include <string>
#include <string_view>

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

    struct Project
    {
        int ID;
        int creatorID;
        std::string name;
        std::string description;
        int completedTasks;
        int totalTasks;

        static bool Validate(std::string_view name, std::string_view description);
        crow::json::wvalue Serialize() const;
    };
}
