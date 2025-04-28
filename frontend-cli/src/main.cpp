#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <glaze/json/write.hpp>
#include <httplib.h>
#include <print>

ftxui::Component HomePage(ftxui::ScreenInteractive& screen)
{
    return ftxui::Container::Vertical({
        ftxui::Renderer([] {
            return ftxui::vbox(
                ftxui::text("Hello world from projecify home page!")
            );
        }),
        ftxui::Button("Exit", screen.ExitLoopClosure())
    });
}

struct TestStruct
{
    int x;
    char c;
    std::string s;
    std::vector<double> d;
};

int main()
{
    TestStruct test{
        10,
        'a',
        "Hello world",
        { 2.3, 4.5, 1.7 }
    };

    std::println("{}", glz::write_json(test).value());

    // auto screen = ftxui::ScreenInteractive::Fullscreen();
    // screen.SetCursor(ftxui::Screen::Cursor{ .shape = ftxui::Screen::Cursor::Hidden });

    // std::string username;
    // std::string password;

    // auto usernameInput = ftxui::Input(&username, "Username");
    // auto passwordInput = ftxui::Input(&password, "Password", ftxui::InputOption{ .password = true });

    // auto layout = ftxui::Container::Vertical({
    //     usernameInput,
    //     passwordInput,
    //     // just for test, no actual login
    //     ftxui::Button("Login", screen.ExitLoopClosure())
    // });

    // auto renderer = ftxui::Renderer(layout, [&] {
    //     return ftxui::vbox({
    //         ftxui::text("projectify"),
    //         ftxui::separator(),
    //         layout->Render()
    //     });
    // });

    // screen.Loop(renderer);
    // screen.Loop(HomePage(screen));



    // httplib::Client cli("localhost", 8000);

    // if (const auto res = cli.Get("/"))
    // {
    //     std::println("Status: {}", res->status);
    //     std::println("Response body: {}", res->body);
    // }
    // else
    //     std::println("Status: {}", res->status);

    return 0;
}
