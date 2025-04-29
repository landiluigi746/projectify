#pragma once

#include "Types.hpp"
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

namespace projcli::Components
{
    namespace Utils
    {
        ftxui::Element Banner();
    }

    class HomePage : public ftxui::ComponentBase
    {
    public:
        HomePage();
        ftxui::Element OnRender() override;
    private:
        ftxui::Component m_SignUpButton;
        ftxui::Component m_SignInButton;
        ftxui::Component m_ExitButton;
    };

    class SignUpPage : public ftxui::ComponentBase
    {
    public:
        SignUpPage();
        ftxui::Element OnRender() override;
    private:
        Credentials m_Credentials;

        ftxui::Component m_UsernameInput;
        ftxui::Component m_PasswordInput;

        ftxui::Component m_SendButton;
        ftxui::Component m_BackButton;
    };

    // class SignInPage;
}
