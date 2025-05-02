#include "Types.hpp"
#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"

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
            Button("Add Task", []{}, ButtonOption::Animated()),
            Button("Back", PagesManager::NavigateTo<DashboardPage>(), ButtonOption::Animated())
        }));

        Add(Components::ToastComponent("Loading tasks...", Components::ToastType::INFO));
    }

    ftxui::Element ProjectDetailsPage::OnRender()
    {
        return vbox({
            Components::Banner(),
            separatorEmpty(),
            ChildAt(0)->Render() | hcenter,
            separatorEmpty(),
            window(
                text("Project Details"),
                vbox({
                    text(std::format("Project Name: {}", m_Project.name)) | bold,
                    separatorEmpty(),
                    paragraph(std::format("Project Description: {}", m_Project.description)),

                    separatorEmpty(),
                    vbox({
                        text("Project Tasks") | bold,
                        ChildAt(ChildCount() - 1)->Render() | size(HEIGHT, EQUAL, 20)
                    }),
                })
            ) | size(WIDTH, EQUAL, 80)
        }) | center;
    }

    void ProjectDetailsPage::OnEnter(const Project& project)
    {
        ChildAt(ChildCount() - 1)->Detach();
        m_Project = project;

        auto makeTask = [&](int i){
            return projcli::Task{
                -1,
                project.ID,
                std::format("Task {}", ++i),
                (i % 3 == 0)
            };
        };

        std::vector<projcli::Task> tasks;
        tasks.reserve(40);

        for (int i = 0; i < 40; ++i)
            tasks.emplace_back(makeTask(i));

        Add(Components::TaskList(tasks));
    }
}
