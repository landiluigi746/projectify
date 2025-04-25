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

    crow::App<projectify::Middleware::RateLimiter> app;

    CROW_ROUTE(app, "/")([]{
       return "Hello world from projectify backend!";
    });

    app.port(projectify::Config::PORT).multithreaded().run();

    return 0;
}
