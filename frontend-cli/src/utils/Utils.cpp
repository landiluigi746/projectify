#include "utils/Utils.hpp"

#include <filesystem>
#include <fstream>

namespace projcli::Utils
{
    std::string GetEnv(std::string_view varName, std::string_view defaultValue)
    {
        const char* val = std::getenv(varName.data());
        return (val && val[0] != '\0') ? std::string(val) : std::string(defaultValue);
    }

    std::filesystem::path GetConfigPath()
    {
    #ifdef _WIN32
        return std::filesystem::path(GetEnv("APPDATA", ".")) / "Projectify";
    #elif __APPLE__ || __linux__
        return std::filesystem::path(GetEnv("HOME", ".")) / ".config/projectify";
    #else
        throw std::runtime_error("Unsupported platform");
    #endif
    }

    bool SaveJWT(std::string_view jwt)
    {
        std::filesystem::path configPath = GetConfigPath();
        std::filesystem::create_directories(configPath);

        std::ofstream file(configPath / "token.txt");

        if (!file.is_open())
            return false;

        file << jwt;
        file.close();

        return true;
    }

    std::string LoadJWT()
    {
        std::filesystem::path configPath = GetConfigPath();
        std::filesystem::create_directories(configPath);

        std::string jwt;
        std::ifstream file(configPath / "token.txt");

        if (!file.is_open())
            return "";

        std::getline(file, jwt);
        file.close();

        return jwt;
    }

    void ClearJWT()
    {
        std::filesystem::remove(GetConfigPath() / "token.txt");
    }
}
