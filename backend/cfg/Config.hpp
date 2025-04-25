#pragma once

#include "utils/Utils.hpp"

#include <string>
#include <string_view>

namespace projectify::Config
{
    inline const auto PORT = std::stoi(projectify::Utils::GetEnv("PORT", "8000"));
}
