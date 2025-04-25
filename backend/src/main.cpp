#include <crow.h>

#include "cfg/Config.hpp"
#include "crow/logging.h"
#include "db/Database.hpp"
#include "logger/Logger.hpp"

int main()
{
    projectify::Logger logger;
    crow::logger::setHandler(&logger);

    if(projectify::Database::Init() == projectify::Database::Result::FAILED)
        return 1;

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]{
       return "Hello world from projectify backend!";
    });

    app.port(projectify::Config::PORT).multithreaded().run();

    return 0;
}
