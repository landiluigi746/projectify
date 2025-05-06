#pragma once

#include <filesystem>
#include <string>
#include <string_view>

namespace projcli::Utils
{
    std::string GetEnv(std::string_view varName, std::string_view defaultValue);
    std::filesystem::path GetConfigPath();

    bool SaveJWT(std::string_view jwt);
    std::string LoadJWT();
    void ClearJWT();
}
