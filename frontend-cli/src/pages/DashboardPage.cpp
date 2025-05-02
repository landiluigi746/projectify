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
    DashboardPage::DashboardPage()
    {
        m_NewProjectButton = Button("Add Project", PagesManager::NavigateTo<NewProjectPage>(), ButtonOption::Animated());

        Add(m_NewProjectButton);
        Add(Components::ToastComponent("Loading projects...", Components::ToastType::INFO));
    }

    void DashboardPage::OnEnter()
    {
        const auto [result, projects] = API::GetInstance().GetProjects();
        ChildAt(ChildCount() - 1)->Detach();

        Add((result.StatusCode == Status::SUCCESS)
            ? Components::ProjectList(projects)
            : Components::ToastComponent("Failed to fetch projects", Components::ToastType::ERROR)
        );
    }

    Element DashboardPage::OnRender()
    {
        return vbox({
            Components::Banner(),
            separatorEmpty(),
            text("Your projects") | hcenter | bold,
            separatorEmpty(),
            ChildAt(0)->Render() | hcenter,
            separatorEmpty(),
            ChildAt(ChildCount() - 1)->Render(),
            separatorEmpty() | yflex
        });
    }
}
