#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "app/ComponentManager.hpp"

using namespace ftxui;

auto screen = ftxui::ScreenInteractive::Fullscreen();

class AboutTest;

class HomeTest : public ftxui::ComponentBase
{
public:
    HomeTest()
    {
        about_button_ = Button("About", projcli::ComponentManager::NavigateTo<AboutTest>());

        Add(Container::Vertical({
            about_button_
        }));
    }

    ftxui::Element OnRender() override
    {
        return vbox({
            text("Hi! This is just a simple test home"),
            about_button_->Render(),
        }) | center | border | flex;
    }

private:
    ftxui::Component about_button_;
};

class AboutTest : public ftxui::ComponentBase
{
public:
    AboutTest()
    {
        home_button_ = Button("Home", projcli::ComponentManager::NavigateTo<HomeTest>());
        exit_button_ = Button("Exit", screen.ExitLoopClosure());

        Add(Container::Horizontal({
            home_button_,
            exit_button_
        }));
    }

    ftxui::Element OnRender() override
    {
        return vbox({
            text("Hi! This is just a simple test about"),
            hbox({
                home_button_->Render(),
                exit_button_->Render(),
            }),
        }) | center | border | flex;
    }

private:
    ftxui::Component home_button_;
    ftxui::Component exit_button_;
};

int main()
{
    projcli::ComponentManager::RegisterComponents<HomeTest, AboutTest>();
    auto tabContainer = projcli::ComponentManager::GetInstance().GetTabContainer();
    screen.Loop(tabContainer);
    return 0;
}
