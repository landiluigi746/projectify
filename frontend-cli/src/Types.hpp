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
        INFO,
        SUCCESS,
        FAILURE
    };

    struct Result
    {
        Status StatusCode;
        std::string Message;
    };

    struct Project
    {
        int ID;
        std::string name;
        std::string description;
        int completedTasks;
        int totalTasks;
    };

    struct Task
    {
        int ID;
        int projectID;
        std::string name;
        bool completed;
    };
}
