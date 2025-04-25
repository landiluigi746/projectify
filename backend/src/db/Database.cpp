#include "db/Database.hpp"
#include "cfg/Config.hpp"

#include <exception>
#include <memory>
#include <mutex>
#include <spdlog/spdlog.h>
#include <tao/pq.hpp>

namespace projectify::Database
{
    static std::shared_ptr<tao::pq::connection_pool> s_ConnectionPool;
    static std::once_flag s_Initialized;
    static Result s_InitResult;

    std::shared_ptr<tao::pq::connection_pool>& GetConnectionPool()
    {
        if(!s_ConnectionPool)
            Init();

        return s_ConnectionPool;
    }

    Result Init()
    {
        std::call_once(s_Initialized, [] {
            try
            {
                s_ConnectionPool = tao::pq::connection_pool::create(Config::DB_CONNECTION_STRING);

                auto conn = s_ConnectionPool->connection();
                bool connectionOpened = conn->is_open();
                spdlog::info("DB connection: {}", (connectionOpened) ? "OPEN" : "CLOSED");

                if(!connectionOpened)
                {
                    s_InitResult = Result::FAILED;
                    return;
                }

                conn->prepare("check_user_exists", R"(
                    SELECT 1
                    FROM users
                    WHERE ID = $1
                )");

                conn->prepare("check_project_exists_name", R"(
                    SELECT 1
                    FROM projects
                    WHERE creatorID = $1 AND name = $2
                )");

                conn->prepare("check_project_exists_id", R"(
                    SELECT 1
                    FROM projects
                    WHERE ID = $1
                )");

                conn->prepare("register_user", R"(
                    INSERT INTO users (username, passwordHash)
                    VALUES ($1, $2)
                    ON CONFLICT DO NOTHING
                    RETURNING id
                )");

                conn->prepare("get_user_credentials", R"(
                    SELECT ID, username, passwordHash
                    FROM users
                    WHERE username = $1
                )");

                conn->prepare("register_project", R"(
                    INSERT INTO projects (creatorID, name, description)
                    VALUES ($1, $2, $3)
                    ON CONFLICT DO NOTHING
                    RETURNING id
                )");

                conn->prepare("get_user_projects", R"(
                    SELECT ID, creatorID, name, description
                    FROM projects
                    WHERE creatorID = $1
                )");

                s_InitResult = Result::SUCCESS;
            }
            catch(const std::exception& e)
            {
                spdlog::error("Database::Init() : {}", e.what());
                s_InitResult = Result::FAILED;
            }
        });

        return s_InitResult;
    }

    bool UserIsPresent(Connection conn, int userID)
    {
        try
        {
            return !conn->execute("check_user_exists", userID).empty();
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::UserIsPresent() : {}", e.what());
            return false;
        }
    }

    bool ProjectIsPresentByName(Connection conn, int userID, std::string_view name)
    {
        try
        {
            return !conn->execute("check_project_exists_name", userID, name).empty();
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::ProjectIsPresentByTitle() : {}", e.what());
            return false;
        }
    }

    bool ProjectIsPresentByID(Connection conn, int projectID)
    {
        try
        {
            return !conn->execute("check_project_exists_id", projectID).empty();
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::ProjectIsPresentByID() : {}", e.what());
            return false;
        }
    }
}
