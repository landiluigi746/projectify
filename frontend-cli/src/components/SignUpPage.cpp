#include "app/ComponentManager.hpp"
#include "components/Components.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Components
{
    SignUpPage::SignUpPage()
    {
        m_UsernameInput = Input(&m_Credentials.username, "Username");
        m_PasswordInput = Input(&m_Credentials.password, "Password", InputOption{ .password = true });

        m_SendButton = Button("Sign Up", []{}, ButtonOption::Animated());
        m_BackButton = Button("Back", ComponentManager::NavigateTo<HomePage>(), ButtonOption::Animated());

        Add(Container::Vertical({
            m_UsernameInput,
            m_PasswordInput,
            m_SendButton,
            m_BackButton
        }));
    }

    Element SignUpPage::OnRender()
    {
        return vbox({
            Utils::Banner(),
            separatorEmpty(),
            window(text("Sign up") | hcenter, vbox({
                m_UsernameInput->Render() | borderRounded,
                m_PasswordInput->Render() | borderRounded,
                separatorEmpty(),
                hbox({
                    m_SendButton->Render(),
                    separatorEmpty(),
                    m_BackButton->Render()
                }) | hcenter
            }))
        }) | center | flex | borderRounded;
    }
}
