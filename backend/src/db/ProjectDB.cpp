#include "db/Database.hpp"
#include "models/Models.hpp"

#include <exception>
#include <spdlog/spdlog.h>
#include <utility>

namespace projectify::Database
{
    static std::pair<int, int> GetTasksStatus(Connection conn, int projectID)
    {
        const auto res = conn->execute("get_tasks_status", projectID);
        return std::make_pair(res[0][0].as<int>(), res[0][1].as<int>());
    }

    std::pair<Result, int> RegisterProject(int userID, std::string_view name, std::string_view description)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();

            if(!UserIsPresent(conn, userID))
                return std::make_pair(Result::NOT_FOUND, -1);

            if(ProjectIsPresentByName(conn, userID, name))
                return std::make_pair(Result::ALREADY_PRESENT, -1);

            const auto tr = conn->transaction();

            const auto res = tr->execute("register_project", userID, name, description);
            tr->commit();

            spdlog::debug("Database::RegisterProject() : Registered project {} by {} with ID {}", name, userID, res[0][0].as<int>());
            return std::make_pair(Result::SUCCESS, res[0][0].as<int>());
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::RegisterProject() : {}", e.what());
            return std::make_pair(Result::FAILED, -1);
        }
    }

    std::pair<Result, std::vector<Models::Project>> GetUserProjects(int userID)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();

            if(!UserIsPresent(conn, userID))
                return std::make_pair(Result::NOT_FOUND, std::vector<Models::Project>());

            const auto res = conn->execute("get_user_projects", userID);

            std::vector<Models::Project> projects;
            projects.reserve(res.size());

            for(const auto& row: res)
            {
                const auto [total, completed] = GetTasksStatus(conn, row[0].as<int>());
                projects.emplace_back(row[0].as<int>(), row[1].as<int>(), row[2].as<std::string>(), row[3].as<std::string>(), completed, total);
            }

            return std::make_pair(Result::SUCCESS, projects);
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::GetUserProjects() : {}", e.what());
            return std::make_pair(Result::FAILED, std::vector<Models::Project>());
        }
    }
}
