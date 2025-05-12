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
    NewTaskPage::NewTaskPage()
    {
        m_TaskNameInput = Input(&m_TaskName, "Task name", InputOption{ .multiline = false });

        m_CreateButton = Button("Create", [&] {
            DoCreateTask();
        }, ButtonOption::Animated());

        m_BackButton = Button("Back", PagesManager::NavigateTo<ProjectDetailsPage>(m_Project), ButtonOption::Animated());

        Add(Container::Vertical({
            m_TaskNameInput,
            m_CreateButton,
            m_BackButton
        }));
    }

    Element NewTaskPage::OnRender()
    {
        return vbox({
            Components::Banner(),
            separatorEmpty(),
            window(
                text(std::format("New task on project: {}", m_Project.name)) | hcenter | bold,
                vbox({
                    paragraph("Name must be between 6 and 64 characters and must start with a letter") | color(Color::Yellow),

                    separatorEmpty(),

                    m_TaskNameInput->Render() | borderRounded,

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

    void NewTaskPage::DoCreateTask()
    {
        m_Result = API::GetInstance().CreateTask(m_Project.ID, std::string_view(m_TaskName));

        if(m_Result.StatusCode == Status::FAILURE)
            return;

        PagesManager::NavigateTo<ProjectDetailsPage>(m_Project)();
    }

    void NewTaskPage::OnEnter(const Project& project)
    {
        m_Project = project;
        m_TaskName.clear();
    }
}
