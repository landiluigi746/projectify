#include "Types.hpp"
#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"
#include "api/API.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/flexbox_config.hpp>

using namespace ftxui;

namespace projcli::Pages
{
    DashboardPage::DashboardPage()
    {
        Add(Container::Horizontal({
            Button("Add Project", PagesManager::NavigateTo<NewProjectPage>(), ButtonOption::Animated()),
            Button("Sign Out", [&](){ API::GetInstance().SignOut(); PagesManager::NavigateTo<HomePage>()(); }, ButtonOption::Animated()),
            Button("Exit", PagesManager::ExitClosure(),  ButtonOption::Animated()),
        }));

        Add(Components::ToastComponent("Loading projects...", Status::INFO));
    }

    void DashboardPage::OnEnter()
    {
        const auto [result, projects] = API::GetInstance().GetProjects();
        ChildAt(ChildCount() - 1)->Detach();

        Add((result.StatusCode == Status::SUCCESS)
            ? Components::ProjectList(projects)
            : Components::ToastComponent("Failed to fetch projects", Status::FAILURE)
        );
    }

    Element DashboardPage::OnRender()
    {
        Element header = vbox({
            Components::Banner(),
            separatorEmpty(),
            text("Your projects") | hcenter | bold,
            separatorEmpty(),
            ChildAt(0)->Render() | hcenter,
            separatorEmpty(),
        });
        header->ComputeRequirement();

        Element content = ChildAt(ChildCount() - 1)->Render();

        int correctContentHeight = PagesManager::Screen().dimy() - header->requirement().min_y;

        return vbox({
            header,
            content | size(HEIGHT, EQUAL, correctContentHeight)
        });
    }
}
