#include "api/API.hpp"
#include "cfg/Config.hpp"
#include "db/Database.hpp"
#include "logger/Logger.hpp"
#include "middleware/Middlewares.hpp"

#include <crow.h>

using namespace projectify;

int main()
{
    Logger logger;
    crow::logger::setHandler(&logger);

    if(Database::Init() == Database::Result::FAILED)
        return 1;

    crow::App<Middleware::RateLimiter, Middleware::JwtValidator> app;

    CROW_ROUTE(app, "/")([]{
        return "Hello world from projectify backend!";
    });

    CROW_ROUTE(app, "/protected")
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
    ([]{
        return "Protected route test";
    });

    CROW_ROUTE(app, "/register")
        .methods("POST"_method)
        (&API::RegisterUser);

    CROW_ROUTE(app, "/login")
        .methods("POST"_method)
        (&API::LoginUser);

    CROW_ROUTE(app, "/registerProject")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::RegisterProject);

    CROW_ROUTE(app, "/getProjects")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::GetProjects);

    app.port(Config::PORT).multithreaded().run();

    return 0;
}
