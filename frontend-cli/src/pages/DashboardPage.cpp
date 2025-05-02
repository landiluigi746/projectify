#include "Types.hpp"
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
        Add(Components::ToastComponent("Loading projects...", Components::ToastType::INFO));
    }

    void DashboardPage::OnEnter()
    {
        const auto [result, projects] = API::GetInstance().GetProjects();
        DetachAllChildren();

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
            ComponentBase::Render(),
            separatorEmpty() | yflex
        });
    }
}
