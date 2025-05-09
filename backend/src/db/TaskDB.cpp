#include "db/Database.hpp"

#include <spdlog/spdlog.h>

namespace projectify::Database
{
    std::pair<Result, int> RegisterTask(int userID, int projectID, std::string_view name)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();

            if(!ProjectIsPresentByID(conn, projectID, userID))
                return std::make_pair(Result::NOT_FOUND, -1);

            if(TaskIsPresentByName(conn, userID, projectID, name))
                return std::make_pair(Result::ALREADY_PRESENT, -1);

            const auto tr = conn->transaction();

            const auto res = tr->execute("register_task", projectID, name);
            tr->commit();

            spdlog::debug("Database::RegisterTask() : Registered task {} by {} with ID {} on project with ID {}", name, res[0][0].as<int>(), userID, projectID);
            return std::make_pair(Result::SUCCESS, res[0][0].as<int>());
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::RegisterTask(): {}", e.what());
            return std::make_pair(Result::FAILED, -1);
        }
    }

    std::pair<Result, std::vector<Models::Task>> GetProjectTasks(int userID, int projectID)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();

            if(!ProjectIsPresentByID(conn, projectID, userID))
                return std::make_pair(Result::NOT_FOUND, std::vector<Models::Task>());

            const auto res = conn->execute("get_tasks", userID, projectID);

            std::vector<Models::Task> tasks;
            tasks.reserve(res.size());

            for(const auto& row: res)
                tasks.emplace_back(row[0].as<int>(), row[1].as<int>(), row[2].as<std::string>(), row[3].as<bool>());

            return std::make_pair(Result::SUCCESS, std::move(tasks));
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::GetProjectTasks(): {}", e.what());
            return std::make_pair(Result::FAILED, std::vector<Models::Task>());
        }
    }

    Result ToggleTaskStatus(int userID, int projectID, int taskID)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();

            if(!TaskIsPresentByID(conn, userID, projectID, taskID))
                return Result::NOT_FOUND;

            const auto tr = conn->transaction();
            tr->execute("toggle_task_status", taskID);
            tr->commit();

            return Result::SUCCESS;
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::ToggleTaskStatus(): {}", e.what());
            return Result::FAILED;
        }
    }

    Result DeleteTask(int userID, int projectID, int taskID)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();

            if(!TaskIsPresentByID(conn, userID, projectID, taskID))
                return Result::NOT_FOUND;

            const auto tr = conn->transaction();
            const auto res = tr->execute("delete_task", taskID);
            tr->commit();

            spdlog::debug("Database::DeleteTask() : Deleted task with ID {} by user with ID {}", projectID, userID);
            return Result::SUCCESS;
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::DeleteTask() : {}", e.what());
            return Result::FAILED;
        }
    }
}
