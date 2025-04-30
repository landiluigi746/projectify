#pragma once

#include <string>

namespace projcli
{
    struct Credentials
    {
        std::string username;
        std::string password;
    };

    enum class Status
    {
        SUCCESS,
        FAILURE
    };

    constexpr const char* StatusToString(Status status) noexcept
    {
        switch(status)
        {
            case Status::SUCCESS:   return "Success";
            case Status::FAILURE:   return "Failure";
        }

        return "Unknown";
    }

    struct Result
    {
        Status StatusCode;
        std::string Message;
    };
}
