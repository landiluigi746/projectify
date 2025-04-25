#include "cfg/Config.hpp"
#include "models/Models.hpp"
#include "utils/Utils.hpp"

namespace projectify::Models
{
    bool User::Validate(std::string_view username, std::string_view password)
    {
        return (
            Utils::RegexMatches(username, Config::USERNAME_REGEX) &&
            Utils::RegexMatches(password, Config::PASSWORD_REGEX)
        );
    }

    crow::json::wvalue User::Serialize() const
    {
        return crow::json::wvalue{
            { "username", username }
        };
    }
}
