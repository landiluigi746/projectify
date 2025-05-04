#include "db/Database.hpp"
#include "models/Models.hpp"

#include <exception>
#include <spdlog/spdlog.h>
#include <utility>

namespace projectify::Database
{
    std::pair<Result, int> RegisterLink(int userID, int projectID, std::string_view name, std::string_view url)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();

            if(!ProjectIsPresentByID(conn, projectID, userID))
                return std::make_pair(Result::NOT_FOUND, -1);

            if(LinkIsPresentByName(conn, userID, projectID, name))
                return std::make_pair(Result::ALREADY_PRESENT, -1);

            const auto tr = conn->transaction();

            const auto res = tr->execute("register_link", projectID, name, url);
            tr->commit();

            spdlog::debug("Database::RegisterLink() : Registered link {} by {} with ID {} on project with ID {}", name, res[0][0].as<int>(), userID, projectID);
            return std::make_pair(Result::SUCCESS, res[0][0].as<int>());
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::RegisterLink(): {}", e.what());
            return std::make_pair(Result::FAILED, -1);
        }
    }

    std::pair<Result, std::vector<Models::Link>> GetProjectLinks(int userID, int projectID)
    {
        try
        {
            const auto conn = GetConnectionPool()->connection();

            if(!ProjectIsPresentByID(conn, projectID, userID))
                return std::make_pair(Result::NOT_FOUND, std::vector<Models::Link>());

            const auto res = conn->execute("get_links", userID, projectID);

            std::vector<Models::Link> links;
            links.reserve(res.size());

            for(const auto& row: res)
                links.emplace_back(row[0].as<int>(), row[1].as<int>(), row[2].as<std::string>(), row[3].as<std::string>());

            return std::make_pair(Result::SUCCESS, std::move(links));
        }
        catch(const std::exception& e)
        {
            spdlog::error("Database::GetProjectLinks(): {}", e.what());
            return std::make_pair(Result::FAILED, std::vector<Models::Link>());
        }
    }
}
