#include "Types.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Pages
{
    DashboardPage::DashboardPage()
    {
        auto makeSampleProject = [] {
            return Project{
                .name = "Sample Project",
                .description =
                    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla eu est cursus,\n"
                    "semper ligula et, maximus velit. Proin eu malesuada enim. Donec a odio sit amet\n"
                    "sem elementum ornare sit amet non felis. Nullam quis est a tellus consequat ultrices.\n"
                    "Sed sed nisl placerat lacus faucibus lacinia.",
                .completedTasks = 4,
                .totalTasks = 10
            };
        };

        Add(Components::ProjectList(std::vector<Project>(8, makeSampleProject())));
    }

    Element DashboardPage::OnRender()
    {
        return vbox({
            Components::Banner() | flex_grow,
            separatorEmpty(),
            text("Your projects") | hcenter | bold,
            separatorEmpty(),
            ComponentBase::Render()
        });
    }
}
