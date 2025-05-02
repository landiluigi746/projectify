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
    Component TaskCard(const Task& task)
    {
        class Impl : public ComponentBase
        {
        public:
            Impl(const Task& task) :
                m_Task(task)
            {
                Add(Checkbox(task.name, &m_Task.completed));
            }

            Element OnRender() override
            {
                Color taskColor = (m_Task.completed ? Color::Green : Color::White);
                return ComponentBase::Render() | color(taskColor);
            }

        private:
            Task m_Task;
        };

        return Make<Impl>(task);
    }
}
