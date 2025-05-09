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
    Component TaskCard(const Task& task, int projectID, Result& resultRef)
    {
        class Impl : public ComponentBase
        {
        public:
            Impl(const Task& task, int projectID, Result& resultRef) :
                m_ProjectID(projectID),
                m_Task(task),
                m_ResultRef(resultRef)
            {
                Add(Container::Horizontal({
                    Checkbox(task.name, &m_Task.completed,
                        CheckboxOption{
                            .on_change = [&] {
                                DoToggleStatus();
                            }
                        }
                    ) | Renderer([](Element inner) {
                        return inner | flex;
                    }),

                    Button(
                        "Delete",
                        [&] {
                            m_ResultRef = API::GetInstance().DeleteTask(m_ProjectID, m_Task.ID);
                            Detach();
                        },
                        ButtonOption::Ascii()
                    )
                }));
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

            int m_ProjectID;
            Task m_Task;
            Result& m_ResultRef;
        };

        return Make<Impl>(task, projectID, resultRef);
    }
}
