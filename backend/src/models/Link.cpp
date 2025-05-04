#include "models/Models.hpp"
#include "utils/Utils.hpp"
#include "cfg/Config.hpp"

namespace projectify::Models
{
    bool Link::Validate(std::string_view name, std::string_view url)
    {
        return (
            Utils::RegexMatches(name, Config::PROJECT_TASK_URL_NAME_REGEX) &&
            Utils::IsURLValid(url)
        );
    }

    crow::json::wvalue Link::Serialize() const
    {
        return crow::json::wvalue{
            { "ID", ID },
            { "projectID", projectID },
            { "name", name },
            { "url", url }
        };
    }
}
