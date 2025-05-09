#include "Types.hpp"
#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"
#include "api/API.hpp"

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
                Add(Container::Horizontal({
                    Button(
                        "See Details",
                        PagesManager::NavigateTo<Pages::ProjectDetailsPage>(m_Project),
                        ButtonOption::Animated()
                    ),

                    Button(
                        "Delete",
                        [&] {
                            API::GetInstance().DeleteProject(m_Project.ID);
                            PagesManager::NavigateTo<Pages::DashboardPage>()();
                        },
                        ButtonOption::Animated()
                    )
                }));
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
                                ((m_Project.totalTasks > 0)
                                    ? vbox({
                                        text(std::format("Completed tasks: {}/{}", m_Project.completedTasks, m_Project.totalTasks)),
                                        gauge((float)m_Project.completedTasks / m_Project.totalTasks) | color(Color::Green) | bgcolor(Color::Red)
                                    })
                                    : text("This project has no tasks.")
                                ),
                                filler(),
                                ComponentBase::Render() | align_right
                            })
                        })
                    ) | size(WIDTH, EQUAL, 70) | hcenter ,
                    separatorEmpty(),
                });
            }
        private:
            Project m_Project;
        };

        return Make<Impl>(project);
    }
}
