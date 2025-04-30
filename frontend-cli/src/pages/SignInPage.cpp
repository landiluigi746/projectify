#include "Types.hpp"
#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"
#include "api/API.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <future>

using namespace ftxui;

namespace projcli::Pages
{
    SignInPage::SignInPage()
    {
        m_UsernameInput = Input(&m_Credentials.username, "Username");
        m_PasswordInput = Input(&m_Credentials.password, "Password", InputOption{ .password = true });

        m_SendButton = Button("Sign In", [&]{
            std::async(std::launch::async, [&]{
                m_Result = API::GetInstance().SignIn(m_Credentials);

                if(m_Result.StatusCode == Status::FAILURE)
                    return;
            }).get();

            std::this_thread::sleep_for(std::chrono::seconds(1));
            PagesManager::NavigateTo<DashboardPage>()();
        }, ButtonOption::Animated());
        m_BackButton = Button("Back", PagesManager::NavigateTo<HomePage>(), ButtonOption::Animated());

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
            Components::Banner(),
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
