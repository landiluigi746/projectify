#include "Types.hpp"
#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"
#include "api/API.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Pages
{
    ProjectDetailsPage::ProjectDetailsPage()
    {
        Add(Container::Horizontal({
            Button("Add Task", PagesManager::NavigateTo<NewTaskPage>(m_Project), ButtonOption::Animated()),
            Button("Add Link", PagesManager::NavigateTo<NewLinkPage>(m_Project), ButtonOption::Animated()),
            Button("Back", PagesManager::NavigateTo<DashboardPage>(), ButtonOption::Animated())
        }));

        Add(Components::ToastComponent("Loading tasks...", Status::INFO));
        Add(Components::ToastComponent("Loading links...", Status::INFO));
    }

    ftxui::Element ProjectDetailsPage::OnRender()
    {
        return vbox({
            Components::Banner(),
            separatorEmpty(),
            ChildAt(0)->Render() | hcenter,
            separatorEmpty(),
            Components::Toast(m_Result.Message, m_Result.StatusCode),
            window(
                text("Project Details"),
                vbox({
                    text(std::format("Project Name: {}", m_Project.name)) | bold,
                    separatorEmpty(),
                    paragraph(std::format("Project Description: {}", m_Project.description)),

                    separatorEmpty(),
                    vbox({
                        text("Project Tasks") | bold,
                        ChildAt(ChildCount() - 2)->Render() | size(HEIGHT, EQUAL, 8)
                    }),

                    separatorEmpty(),
                    vbox({
                        text("Project Links") | bold,
                        ChildAt(ChildCount() - 1)->Render() | size(HEIGHT, EQUAL, 6)
                    })
                })
            ) | size(WIDTH, EQUAL, 80)
        }) | center;
    }

    void ProjectDetailsPage::OnEnter(const Project& project)
    {
        m_Project = project;

        const auto [resultTasks, tasks] = API::GetInstance().GetTasks(project.ID);

        ChildAt(ChildCount() - 2) = (
            (resultTasks.StatusCode == Status::SUCCESS)
            ? Components::TaskList(tasks, m_Result)
            : Components::ToastComponent("Failed to load tasks", Status::FAILURE)
        );

        const auto [resultLinks, links] = API::GetInstance().GetLinks(project.ID);

        ChildAt(ChildCount() - 1) = (
            (resultLinks.StatusCode == Status::SUCCESS)
            ? Components::LinkList(links)
            : Components::ToastComponent("Failed to load links", Status::FAILURE)
        );
    }
}
