#pragma once

#include "Types.hpp"
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

namespace projcli::Pages
{
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
        void DoSignUp();

        Credentials m_Credentials;
        Result m_Result;

        ftxui::Component m_UsernameInput;
        ftxui::Component m_PasswordInput;

        ftxui::Component m_SendButton;
        ftxui::Component m_BackButton;
    };

    class SignInPage : public ftxui::ComponentBase
    {
    public:
        SignInPage();
        ftxui::Element OnRender() override;
    private:
        void DoSignIn();

        Credentials m_Credentials;
        Result m_Result;

        ftxui::Component m_UsernameInput;
        ftxui::Component m_PasswordInput;

        ftxui::Component m_SendButton;
        ftxui::Component m_BackButton;
    };

    class DashboardPage : public ftxui::ComponentBase
    {
    public:
        DashboardPage();
        ftxui::Element OnRender() override;
        void OnEnter();
    };

    class NewProjectPage : public ftxui::ComponentBase
    {
    public:
        NewProjectPage();
        ftxui::Element OnRender() override;
    private:
        void DoCreateProject();

        std::string m_ProjectName;
        std::string m_ProjectDescription;
        Result m_Result;

        ftxui::Component m_ProjectNameInput;
        ftxui::Component m_ProjectDescriptionInput;
        ftxui::Component m_CreateButton;
        ftxui::Component m_BackButton;
    };

    class ProjectDetailsPage : public ftxui::ComponentBase
    {
    public:
        ProjectDetailsPage();
        ftxui::Element OnRender() override;
        void OnEnter(const Project& project);
    private:
        Project m_Project;
        Result m_Result;
    };

    class NewTaskPage : public ftxui::ComponentBase
    {
    public:
        NewTaskPage();
        ftxui::Element OnRender() override;
        void OnEnter(const Project& project);
    private:
        void DoCreateTask();

        Project m_Project;
        std::string m_TaskName;
        Result m_Result;

        ftxui::Component m_TaskNameInput;
        ftxui::Component m_CreateButton;
        ftxui::Component m_BackButton;
    };

    class NewLinkPage : public ftxui::ComponentBase
    {
    public:
        NewLinkPage();
        ftxui::Element OnRender() override;
        void OnEnter(const Project& project);
    private:
        void DoCreateLink();

        Project m_Project;
        std::string m_LinkName;
        std::string m_LinkURL;
        Result m_Result;

        ftxui::Component m_LinkNameInput;
        ftxui::Component m_LinkURLInput;
        ftxui::Component m_CreateButton;
        ftxui::Component m_BackButton;
    };
}
