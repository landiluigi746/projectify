#include "Types.hpp"
#include "app/ComponentManager.hpp"
#include "components/Components.hpp"
#include "api/API.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <future>

using namespace ftxui;

namespace projcli::Components
{
    SignInPage::SignInPage()
    {
        m_UsernameInput = Input(&m_Credentials.username, "Username");
        m_PasswordInput = Input(&m_Credentials.password, "Password", InputOption{ .password = true });

        m_SendButton = Button("Sign In", [&]{
            std::async(std::launch::async, [&]{
                m_Result = API::GetInstance().SignIn(m_Credentials);
            }).get();
        }, ButtonOption::Animated());
        m_BackButton = Button("Back", ComponentManager::NavigateTo<HomePage>(), ButtonOption::Animated());

        Add(Container::Vertical({
            m_UsernameInput,
            m_PasswordInput,
            m_SendButton,
            m_BackButton
        }));
    }

    Element SignInPage::OnRender()
    {
        return vbox({
            Utils::Banner(),
            separatorEmpty(),
            window(text("Sign in") | hcenter, vbox({
                m_UsernameInput->Render() | borderRounded,
                m_PasswordInput->Render() | borderRounded,
                separatorEmpty(),
                (m_Result.Message.empty()) ?
                emptyElement() :
                text(m_Result.Message) | hcenter,
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
