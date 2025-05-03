#include "Types.hpp"
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
    Component TaskCard(const Task& task, Result& resultRef)
    {
        class Impl : public ComponentBase
        {
        public:
            Impl(const Task& task, Result& resultRef) :
                m_Task(task),
                m_ResultRef(resultRef)
            {
                Add(Checkbox(task.name, &m_Task.completed,
                    CheckboxOption{
                        .on_change = [&] {
                            DoToggleStatus();
                        }
                    }
                ));
            }

            Element OnRender() override
            {
                Color taskColor = (m_Task.completed ? Color::Green : Color::White);
                return ComponentBase::Render() | color(taskColor);
            }
        private:
            void DoToggleStatus()
            {
                const auto result = API::GetInstance().ToggleTaskStatus(m_Task.projectID, m_Task.ID);

                if(result.StatusCode == Status::FAILURE)
                    m_Task.completed = !m_Task.completed;

                m_ResultRef = result;
            }

            Task m_Task;
            Result& m_ResultRef;
        };

        return Make<Impl>(task, resultRef);
    }
}
