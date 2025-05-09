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
        void SignOut();

        std::pair<Result, std::vector<Project>> GetProjects();
        Result CreateProject(std::string_view name, std::string_view description);
        Result DeleteProject(int projectID);

        std::pair<Result, std::vector<Task>> GetTasks(int projectID);
        Result CreateTask(int projectID, std::string_view name);
        Result ToggleTaskStatus(int projectID, int taskID);
        Result DeleteTask(int projectID, int taskID);

        std::pair<Result, std::vector<Link>> GetLinks(int projectID);
        Result CreateLink(int projectID, std::string_view name, std::string_view url);
    private:
        API();

        httplib::Client m_Client;
    };
}
