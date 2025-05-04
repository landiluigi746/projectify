#include "Types.hpp"
#include "components/Components.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Components
{
    Component TaskList(const std::vector<Task>& tasks, Result& resultRef)
    {
        class Impl : public ComponentBase
        {
        public:
            Impl(const std::vector<Task>& tasks, Result& resultRef)
            {
                if(!tasks.empty())
                {
                    m_TasksContainer = Container::Vertical({});

                    for (const auto& task : tasks)
                        m_TasksContainer->Add(TaskCard(task, resultRef));

                    Add(Renderer(m_TasksContainer, [&] {
                        return m_TasksContainer->Render() | vscroll_indicator | yframe;
                    }));
                }
                else
                {
                    Add(Renderer([] {
                        return text("This project has no tasks") | color(Color::Yellow) | bold;
                    }));
                }
            }
        private:
            Component m_TasksContainer;
        };

        return Make<Impl>(tasks, resultRef);
    }
}
