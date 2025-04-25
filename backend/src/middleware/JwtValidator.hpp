#pragma once

#include <crow.h>
#include <utility>
#include <string>

namespace crow
{
    struct request;
    struct response;
}

namespace projectify::Middleware
{
    struct JwtValidator : crow::ILocalMiddleware
    {
        struct context {};

        void before_handle(crow::request& req, crow::response& res, context& ctx);
        void after_handle(crow::request& req, crow::response& res, context& ctx) {}

    private:
        std::pair<bool, std::string> VerifyToken(const std::string& token);
    };
}
