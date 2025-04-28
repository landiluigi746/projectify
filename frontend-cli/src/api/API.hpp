#pragma once

#include "Types.hpp"

#include <httplib.h>

namespace projcli::API
{
    enum class Status
    {
        SUCCESS,
        FAILURE
    };

    constexpr const char* StatusToString(Status status)
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

    class API
    {
    public:
        API();

        Result SignUp(const Credentials& credentials);
        Result SignIn(const Credentials& credentials);

        Result TestSignedIn();
    private:
        httplib::Client m_Client;
    };
}
