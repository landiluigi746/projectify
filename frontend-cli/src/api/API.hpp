#pragma once

#include "Types.hpp"

#include <httplib.h>

namespace projcli
{
    class API
    {
    public:
        static API& GetInstance();

        Result SignUp(const Credentials& credentials);
        Result SignIn(const Credentials& credentials);
        Result SignInWithStoredJWT();
    private:
        API();

        httplib::Client m_Client;
    };
}
