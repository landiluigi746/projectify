#include "Types.hpp"
#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"
#include "api/API.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Pages
{
    SignUpPage::SignUpPage()
    {
        m_UsernameInput = Input(&m_Credentials.username, "Username");
        m_PasswordInput = Input(&m_Credentials.password, "Password", InputOption{ .password = true });

        m_SendButton = Button("Sign Up", [&]{
            DoSignUp();
        }, ButtonOption::Animated());
        m_BackButton = Button("Back", PagesManager::NavigateTo<HomePage>(), ButtonOption::Animated());

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
            Components::Banner(),
            separatorEmpty(),
            window(text("Sign up") | hcenter, vbox({
                m_UsernameInput->Render() | borderRounded,
                m_PasswordInput->Render() | borderRounded,

                Components::Toast(m_Result.Message, m_Result.StatusCode),

                hbox({
                    m_SendButton->Render(),
                    separatorEmpty(),
                    m_BackButton->Render()
                }) | hcenter
            }))
        }) | center | flex | borderRounded;
    }

    void SignUpPage::DoSignUp()
    {
        m_Result = API::GetInstance().SignUp(m_Credentials);

        if(m_Result.StatusCode == Status::FAILURE)
            return;

        PagesManager::NavigateTo<DashboardPage>()();
    }

    void SignUpPage::OnEnter()
    {
        m_Credentials.username.clear();
        m_Credentials.password.clear();
    }
}
