#include "models/Models.hpp"
#include "utils/Utils.hpp"
#include "cfg/Config.hpp"

namespace projectify::Models
{
    bool Task::Validate(std::string_view name)
    {
        return (
            Utils::RegexMatches(name, Config::PROJECT_TASK_URL_NAME_REGEX)
        );
    }

    crow::json::wvalue Task::Serialize() const
    {
        return crow::json::wvalue{
            { "ID", ID },
            { "projectID", projectID },
            { "name", name },
            { "completed", completed }
        };
    }
}