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
    Component LinkCard(const Link& link, int projectID, Result& resultRef)
    {
        class Impl : public ComponentBase
        {
        public:
            Impl(const Link& link, int projectID, Result& resultRef) :
                m_ProjectID(projectID),
                m_Link(link),
                m_ResultRef(resultRef)
            {
                Add(Container::Horizontal({
                    Button(m_Link.name, []{}, ButtonOption{
                        .transform = [&](const EntryState& e) {
                            return text(e.label) | hyperlink(m_Link.url) | size(WIDTH, EQUAL, m_Link.name.length() - 2);
                        }
                    }) | Renderer([](Element inner) {
                        return inner | flex;
                    }),

                    Button(
                        "Delete",
                        [&] {
                            m_ResultRef = API::GetInstance().DeleteLink(m_ProjectID, m_Link.ID);
                            Detach();
                        },
                        ButtonOption::Ascii()
                    )
                }));
            }
        private:
            int m_ProjectID;
            Link m_Link;
            Result& m_ResultRef;
        };

        return Make<Impl>(link, projectID, resultRef);
    }
}
