#include "middleware/RateLimiter.hpp"
#include "cfg/Config.hpp"

#include <chrono>
#include <crow.h>

namespace projectify::Middleware
{
    void RateLimiter::before_handle(crow::request& req, crow::response& res, context& ctx)
    {
        const std::string ip = req.remote_ip_address;
        const auto now = std::chrono::steady_clock::now();

        std::lock_guard lock(m_Mutex);

        if(!m_ClientMap.contains(ip))
        {
            m_ClientMap.emplace(ip, ClientInfo {
                1,
                std::chrono::steady_clock::now()
            });
            return;
        }

        ClientInfo& clientInfo = m_ClientMap[ip];

        if(now - clientInfo.WindowStart >= Config::TIME_WINDOW)
        {
            clientInfo.RequestsCount = 1;
            clientInfo.WindowStart = now;
        }

        if(clientInfo.RequestsCount > Config::REQUESTS_PER_MINUTE)
        {
            res.code = crow::status::TOO_MANY_REQUESTS;
            res.add_header("Retry-After", std::to_string(std::chrono::duration_cast<std::chrono::seconds>(Config::TIME_WINDOW).count()));
            res.end("Too many requests. Please try again later");
            return;
        }

        ++clientInfo.RequestsCount;
    }
}
