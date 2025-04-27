#pragma once

#include "models/Models.hpp"

#include <cstdint>
#include <tao/pq/connection.hpp>
#include <tao/pq/connection_pool.hpp>

namespace projectify::Database
{
    enum class Result : uint8_t
    {
        SUCCESS,
        FAILED,
        ALREADY_PRESENT,
        NOT_FOUND,
        INVALID_CREDENTIALS,
    };

    using Connection = std::shared_ptr<tao::pq::connection>;

    std::shared_ptr<tao::pq::connection_pool>& GetConnectionPool();
    Result Init();

    bool UserIsPresent(Connection conn, int userID);
    bool ProjectIsPresentByID(Connection conn, int projectID, int userID);
    bool ProjectIsPresentByName(Connection conn, int userID, std::string_view name);
    bool TaskIsPresentByID(Connection conn, int userID, int projectID, int taskID);
    bool TaskIsPresentByName(Connection conn, int userID, int projectID, std::string_view name);

    std::pair<Result, int> RegisterUser(std::string_view username, std::string_view password);
    std::pair<Result, std::optional<Models::User>> GetUserByCredentials(std::string_view username, std::string_view password);

    std::pair<Result, int> RegisterProject(int userID, std::string_view name, std::string_view description);
    std::pair<Result, std::vector<Models::Project>> GetUserProjects(int userID);

    std::pair<Result, int> RegisterTask(int userID, int projectID, std::string_view name);
    std::pair<Result, std::vector<Models::Task>> GetProjectTasks(int userID, int projectID);
    Result ToggleTaskStatus(int userID, int projectID, int taskID);
}
