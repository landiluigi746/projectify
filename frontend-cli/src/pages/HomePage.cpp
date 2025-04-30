#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Pages
{
    HomePage::HomePage()
    {
        m_SignInButton = Button("Sign In", PagesManager::NavigateTo<SignInPage>(), ButtonOption::Animated());
        m_SignUpButton = Button("Sign Up", PagesManager::NavigateTo<SignUpPage>(), ButtonOption::Animated());
        m_ExitButton = Button("Exit", PagesManager::ExitClosure(), ButtonOption::Animated());

        Add(Container::Vertical({
            m_SignInButton,
            m_SignUpButton,
            m_ExitButton
        }));
    }

    Element HomePage::OnRender()
    {
        return vbox({
            Components::Banner(),
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
}
