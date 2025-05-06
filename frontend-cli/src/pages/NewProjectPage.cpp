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
    NewProjectPage::NewProjectPage()
    {
        m_ProjectNameInput = Input(&m_ProjectName, "Project name");
        m_ProjectDescriptionInput = Input(&m_ProjectDescription, "Project description");

        m_CreateButton = Button("Create", [&]{
            DoCreateProject();
        }, ButtonOption::Animated());

        m_BackButton = Button("Back", PagesManager::GetInstance().NavigateTo<DashboardPage>(), ButtonOption::Animated());

        Add(Container::Vertical({
            m_ProjectNameInput,
            m_ProjectDescriptionInput,
            m_CreateButton,
            m_BackButton
        }));
    }

    Element NewProjectPage::OnRender()
    {
        return vbox({
            Components::Banner(),
            separatorEmpty(),
            window(
                text("New project") | hcenter | bold,
                vbox({
                    m_ProjectNameInput->Render() | borderRounded,
                    m_ProjectDescriptionInput->Render() | borderRounded,

                    Components::Toast(m_Result.Message, m_Result.StatusCode),

                    hbox({
                        m_CreateButton->Render(),
                        separatorEmpty(),
                        m_BackButton->Render()
                    }) | hcenter
                })
            ) | size(WIDTH, EQUAL, 70)
        }) | center | yflex;
    }

    void NewProjectPage::DoCreateProject()
    {
        m_Result = API::GetInstance().CreateProject(m_ProjectName, m_ProjectDescription);

        if(m_Result.StatusCode == Status::FAILURE)
            return;

        PagesManager::NavigateTo<DashboardPage>()();
    }
}
