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
#include <future>

using namespace ftxui;

namespace projcli::Pages
{
    static std::future<void> s_Future;
    static std::mutex s_Mutex;

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
        auto toast = (m_Result.Message.empty())
            ? emptyElement()
            : Components::Toast(m_Result.Message,
                (m_Result.StatusCode == Status::SUCCESS)
                ? Components::ToastType::SUCCESS
                : Components::ToastType::ERROR
            );

        return vbox({
            Components::Banner(),
            separatorEmpty(),
            window(
                text("Sign in") | hcenter,
                vbox({
                    m_UsernameInput->Render() | borderRounded,
                    m_PasswordInput->Render() | borderRounded,

                    std::move(toast),

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
        s_Future = std::async(std::launch::async, [&]{
            {
                std::lock_guard<std::mutex> lock(s_Mutex);
                m_Result = API::GetInstance().SignIn(m_Credentials);

                if(m_Result.StatusCode == Status::FAILURE)
                    return;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::lock_guard<std::mutex> lock(s_Mutex);
            PagesManager::NavigateTo<DashboardPage>()();
        });
    }

}
