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
    Component LinkCard(const Link& link)
    {
        class Impl : public ComponentBase
        {
        public:
            Impl(const Link& link) :
                m_Link(link)
            {
                Add(Button(m_Link.name, []{}, ButtonOption{
                    .transform = [&](const EntryState& e) {
                        return text(e.label) | hyperlink(m_Link.url) | size(WIDTH, EQUAL, m_Link.name.length() - 2);
                    }
                }));
            }
        private:
            Link m_Link;
        };

        return Make<Impl>(link);
    }
}
