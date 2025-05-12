#include "Types.hpp"
#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"
#include "api/API.hpp"

#include <cmath>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Pages
{
    SignInPage::SignInPage()
    {
        m_UsernameInput = Input(&m_Credentials.username, "Username");
        m_PasswordInput = Input(&m_Credentials.password, "Password", InputOption{ .password = true });

        m_SendButton = Button("Sign In", [&]{
            DoSignIn();
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
            window(
                text("Sign in") | hcenter,
                vbox({
                    m_UsernameInput->Render() | borderRounded,
                    m_PasswordInput->Render() | borderRounded,

                    Components::Toast(m_Result.Message, m_Result.StatusCode),

                    hbox({
                        m_SendButton->Render(),
                        separatorEmpty(),
                        m_BackButton->Render()
                    }) | hcenter
                })
            )
        }) | center | flex | borderRounded;
    }

    void SignInPage::DoSignIn()
    {
        m_Result = API::GetInstance().SignIn(m_Credentials);

        if(m_Result.StatusCode == Status::FAILURE)
            return;

        PagesManager::NavigateTo<DashboardPage>()();
    }

    void SignInPage::OnEnter()
    {
        m_Credentials.username.clear();
        m_Credentials.password.clear();
    }
}
