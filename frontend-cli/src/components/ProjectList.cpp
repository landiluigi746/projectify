#include "Types.hpp"
#include "components/Components.hpp"

#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Components
{
    Component ProjectList(const std::vector<Project>& projects)
    {
        class Impl : public ComponentBase
        {
        public:
            Impl(const std::vector<Project>& projects)
            {
                if(!projects.empty())
                {
                    m_ProjectsContainer = Container::Vertical({});

                    for(const auto& project : projects)
                        m_ProjectsContainer->Add(ProjectCard(project));

                    Add(Renderer(m_ProjectsContainer, [&] {
                        return m_ProjectsContainer->Render() | vscroll_indicator | yframe;
                    }));
                }
                else
                {
                    Add(Renderer([&] {
                        return text("You currently have no projects") | hcenter |color(Color::Yellow) | bold;
                    }));
                }
            }
        private:
            ftxui::Component m_ProjectsContainer;
        };

        return Make<Impl>(projects);
    }
}
