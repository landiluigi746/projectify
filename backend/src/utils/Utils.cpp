#include "utils/Utils.hpp"

#include <cstdlib>
#include <string>
#include <string_view>

namespace projectify::Utils
{
    std::string GetEnv(std::string_view varName, std::string_view defaultValue)
    {
        const char* val = std::getenv(varName.data());
        return (val && val[0] != '\0') ? std::string(val) : std::string(defaultValue);
    }
}
