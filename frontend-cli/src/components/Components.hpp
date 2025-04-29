#pragma once

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
    private:
        ftxui::Component m_SignUpButton;
        ftxui::Component m_SignInButton;
        ftxui::Component m_ExitButton;
    };

    // class SignUpPage;
    // class SignInPage;
}
