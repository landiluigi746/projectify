#include "api/API.hpp"
#include "cfg/Config.hpp"
#include "db/Database.hpp"
#include "logger/Logger.hpp"
#include "middleware/Middlewares.hpp"

#include <crow.h>

int main()
{
    projectify::Logger logger;
    crow::logger::setHandler(&logger);

    if(projectify::Database::Init() == projectify::Database::Result::FAILED)
        return 1;

    crow::App<projectify::Middleware::RateLimiter, projectify::Middleware::JwtValidator> app;

    CROW_ROUTE(app, "/")([]{
        return "Hello world from projectify backend!";
    });

    CROW_ROUTE(app, "/protected")
        .CROW_MIDDLEWARES(app, projectify::Middleware::JwtValidator)
    ([]{
        return "Protected route test";
    });

    CROW_ROUTE(app, "/register")
        .methods("POST"_method)
    ([] (const crow::request& req, crow::response& res) {
        projectify::API::RegisterUser(req, res);
    });

    CROW_ROUTE(app, "/login")
        .methods("POST"_method)
    ([] (const crow::request& req, crow::response& res) {
        projectify::API::LoginUser(req, res);
    });

    app.port(projectify::Config::PORT).multithreaded().run();

    return 0;
}
