#include "app/ComponentManager.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace projcli
{
    ComponentManager::ComponentManager() :
        m_Selected(0),
        m_Screen(ftxui::ScreenInteractive::Fullscreen())
    {}

    ComponentManager& ComponentManager::GetInstance()
    {
        static ComponentManager instance;
        return instance;
    }

    void ComponentManager::MainLoop()
    {
        m_Screen.Loop(GetTabContainer());
    }

    ftxui::Component ComponentManager::GetTabContainer()
    {
        ftxui::Components components;

        for(auto& [name, component]: m_Components)
            components.emplace_back(component);

        return ftxui::Container::Tab(components, &m_Selected);
    }
}
