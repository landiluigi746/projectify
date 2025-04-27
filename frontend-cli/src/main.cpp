#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <httplib.h>
#include <print>

int main()
{
    // using namespace ftxui;

    // auto document = vbox({
    //     hbox({
    //         text("one") | border,
    //         text("two") | border | flex,
    //         text("three") | border | flex,
    //     }),

    //     gauge(0.25) | color(Color::Red),
    //     gauge(0.50) | color(Color::White),
    //     gauge(0.75) | color(Color::Blue),
    // });

    // auto screen = Screen::Create(Dimension::Fit(document));
    // Render(screen, document);

    // screen.Print();

    httplib::Client cli("localhost", 8000);

    if (const auto res = cli.Get("/"))
    {
        std::println("Status: {}", res->status);
        std::println("Response body: {}", res->body);
    }
    else
        std::println("Status: {}", res->status);

    return 0;
}
