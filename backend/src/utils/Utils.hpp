#pragma once

#include <string_view>

namespace projectify::Utils
{
    std::string GetEnv(std::string_view varName, std::string_view defaultValue);

    std::string HashString(std::string_view string);
    bool CheckHashedString(std::string_view string, std::string_view hashed);

    bool RegexMatches(std::string_view str, const std::regex& regex);
}
