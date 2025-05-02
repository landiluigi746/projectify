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
    {}

    void DashboardPage::OnEnter()
    {
        const auto [result, projects] = API::GetInstance().GetProjects();

        if(result.StatusCode == Status::FAILURE)
        {
            Add(Renderer([] {
                return vbox({
                    text("Failed to fetch projects") | hcenter | bold,
                    separatorEmpty(),
                    text("Please try again later") | hcenter
                });
            }));

            return;
        }

        Add(Components::ProjectList(projects));
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
