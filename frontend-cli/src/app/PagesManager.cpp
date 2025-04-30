#include "app/PagesManager.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace projcli
{
    PagesManager::PagesManager() :
        m_Selected(0),
        m_Screen(ftxui::ScreenInteractive::Fullscreen())
    {}

    PagesManager& PagesManager::GetInstance()
    {
        static PagesManager instance;
        return instance;
    }

    void PagesManager::MainLoop()
    {
        m_Screen.Loop(GetTabContainer());
    }

    ftxui::Component PagesManager::GetTabContainer()
    {
        ftxui::Components pages;

        for(auto& [name, page]: m_Pages)
            pages.emplace_back(page);

        return ftxui::Container::Tab(pages, &m_Selected);
    }
}
