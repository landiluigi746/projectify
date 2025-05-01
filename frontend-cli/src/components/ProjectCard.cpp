#include "Types.hpp"
#include "components/Components.hpp"

#include <cmath>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Components
{
    Component ProjectCard(const Project& project)
    {
        class Impl : public ComponentBase
        {
        public:
            Impl(const Project& project) :
                m_Project(project)
            {
                Add(ftxui::Button("See Details", []{}, ButtonOption::Animated()));
            }

            Element OnRender() override
            {
                return vbox({
                    window(
                        text(m_Project.name),
                        vbox({
                            paragraph(m_Project.description),
                            separatorEmpty(),
                            hbox({
                                vbox({
                                    text(std::format("Completed tasks: {}/{}", m_Project.completedTasks, m_Project.totalTasks)),
                                    gauge((float)m_Project.completedTasks / m_Project.totalTasks)
                                }),
                                filler(),
                                ComponentBase::Render() | align_right
                            }),
                            separatorEmpty()
                        })
                    ) | hcenter,
                    separatorEmpty(),
                });
            }
        private:
            Project m_Project;
        };

        return Make<Impl>(project);
    }
}
