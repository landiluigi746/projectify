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
            Components::Toast(m_TaskResult.Message, m_TaskResult.StatusCode),
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

        const auto [result, tasks] = API::GetInstance().GetTasks(project.ID);

        ChildAt(ChildCount() - 2) = (
            (result.StatusCode == Status::SUCCESS)
            ? Components::TaskList(tasks, m_TaskResult)
            : Components::ToastComponent("Failed to load tasks", Status::FAILURE)
        );

        auto makeSampleLink = [] {
            return Link{ -1, -1, "ciao", "https://www.google.com" };
        };

        std::vector<Link> links;
        links.reserve(12);

        for(int i = 0; i < 12; i++)
            links.emplace_back(makeSampleLink());

        ChildAt(ChildCount() - 1) = (Components::LinkList(links));
    }
}
