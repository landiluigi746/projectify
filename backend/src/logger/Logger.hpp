#pragma once

#include <crow/logging.h>
#include <spdlog/spdlog.h>

namespace projectify
{
    class Logger : public crow::ILogHandler
    {
    public:
        Logger() = default;

        void log(std::string message, crow::LogLevel level)
        {
            switch(level)
            {
                case crow::LogLevel::DEBUG:     spdlog::debug("{}", message); break;
                case crow::LogLevel::INFO:      spdlog::info("{}", message); break;
                case crow::LogLevel::WARNING:   spdlog::warn("{}", message); break;
                case crow::LogLevel::ERROR:     spdlog::error("{}", message); break;
                case crow::LogLevel::CRITICAL:  spdlog::critical("{}", message); break;
            }
        }
    };
}
