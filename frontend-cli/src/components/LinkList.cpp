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
    Component LinkList(const std::vector<Link>& links)
    {
        class Impl : public ComponentBase
        {
        public:
            Impl(const std::vector<Link>& links)
            {
                if(!links.empty())
                {
                    m_LinksContainer = Container::Vertical({});

                    for(const auto& link: links)
                        m_LinksContainer->Add(LinkCard(link));

                    Add(Renderer(m_LinksContainer, [&] {
                        return m_LinksContainer->Render() | vscroll_indicator | yframe;
                    }));
                }
                else
                {
                    Add(Renderer([] {
                        return text("This project has no links") | color(Color::Yellow) | bold;
                    }));
                }
            }
        private:
            Component m_LinksContainer;
        };

        return Make<Impl>(links);
    }
}
