#include "cfg/Config.hpp"
#include "crow/json.h"
#include "models/Models.hpp"
#include "utils/Utils.hpp"

namespace projectify::Models
{
    bool Project::Validate(std::string_view name, std::string_view description)
    {
        return (
            Utils::RegexMatches(name, Config::PROJECT_TASK_URL_NAME_REGEX) &&
            !description.empty() && description.length() < 512
        );
    }

    crow::json::wvalue Project::Serialize() const
    {
        return crow::json::wvalue{
            { "name", name },
            { "description", description },
            { "completedTasks", completedTasks },
            { "totalTasks", totalTasks }
        };
    }
}
