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

        std::pair<Result, std::vector<Project>> GetProjects();
        Result CreateProject(std::string_view name, std::string_view description);
    private:
        API();

        httplib::Client m_Client;
    };
}
