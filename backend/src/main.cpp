#include "api/API.hpp"
#include "cfg/Config.hpp"
#include "db/Database.hpp"
#include "logger/Logger.hpp"
#include "middleware/JwtValidator.hpp"
#include "middleware/Middlewares.hpp"

#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_response.h>

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

    CROW_ROUTE(app, "/users/loginJWT")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
    ([]{
        return crow::status::OK;
    });

    CROW_ROUTE(app, "/users/register")
        .methods("POST"_method)
        (&API::RegisterUser);

    CROW_ROUTE(app, "/users/login")
        .methods("POST"_method)
        (&API::LoginUser);

    CROW_ROUTE(app, "/projects/register")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::RegisterProject);

    CROW_ROUTE(app, "/projects/get")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::GetProjects);

    CROW_ROUTE(app, "/projects/delete")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::DeleteProject);

    CROW_ROUTE(app, "/tasks/register")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::RegisterTask);

    CROW_ROUTE(app, "/tasks/get")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::GetTasks);

    CROW_ROUTE(app, "/tasks/toggleStatus")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::ToggleTaskStatus);

    CROW_ROUTE(app, "/tasks/delete")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::DeleteTask);

    CROW_ROUTE(app, "/links/register")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::RegisterLink);

    CROW_ROUTE(app, "/links/get")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::GetLinks);

    CROW_ROUTE(app, "/links/delete")
        .methods("POST"_method)
        .CROW_MIDDLEWARES(app, Middleware::JwtValidator)
        (&API::DeleteLink);

    app.port(Config::PORT).multithreaded().run();

    return 0;
}
