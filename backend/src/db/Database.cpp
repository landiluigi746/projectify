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

                const auto res = conn->execute("SELECT 1");
                spdlog::info("{}", res[0].as<int>());

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
}
