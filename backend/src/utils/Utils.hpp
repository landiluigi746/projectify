#pragma once

#include <string_view>

namespace projectify::Utils
{
    std::string GetEnv(std::string_view varName, std::string_view defaultValue);
}
