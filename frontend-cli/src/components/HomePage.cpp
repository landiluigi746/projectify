#include "app/ComponentManager.hpp"
#include "components/Components.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Components
{
    HomePage::HomePage()
    {
        m_SignInButton = Button("Sign In", []{});
        m_SignUpButton = Button("Sign Up", []{});
        m_ExitButton = Button("Exit", ComponentManager::ExitClosure());

        Add(Container::Vertical({
            m_SignInButton,
            m_SignUpButton,
            m_ExitButton
        }));
    }

    Element HomePage::OnRender()
    {
        return vbox({
            Banner(),
            separatorEmpty(),
            paragraphAlignCenter(
                "Your go-to solution to organize projects and related links.\n"
                "Organize projects smarter, achieve results faster."
            ),
            separatorEmpty(),
            hbox({
                m_SignUpButton->Render(),
                separatorEmpty(),
                m_SignInButton->Render()
            }) | hcenter,
            separatorEmpty(),
            m_ExitButton->Render() | hcenter
        }) | center | flex | borderRounded;
    }

    Element HomePage::Banner()
    {
        return vbox({
            text(R"(                     _              _    _   __        )"),
            text(R"(                    (_)            | |  (_) / _|       )"),
            text(R"(  _ __   _ __  ___   _   ___   ___ | |_  _ | |_  _   _ )"),
            text(R"( | '_ \ | '__|/ _ \ | | / _ \ / __|| __|| ||  _|| | | |)"),
            text(R"( | |_) || |  | (_) || ||  __/| (__ | |_ | || |  | |_| |)"),
            text(R"( | .__/ |_|   \___/ | | \___| \___| \__||_||_|   \__, |)"),
            text(R"( | |               _/ |                           __/ |)"),
            text(R"( |_|              |__/                           |___/ )")
        }) | hcenter;
    }

}
