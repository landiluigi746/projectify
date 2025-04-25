#include <crow.h>

#include "cfg/Config.hpp"
#include "crow/logging.h"
#include "logger/Logger.hpp"

int main()
{
    projectify::Logger logger;
    crow::logger::setHandler(&logger);

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]{
       return "Hello world from projectify backend!";
    });

    app.port(projectify::Config::PORT).multithreaded().run();

    return 0;
}
