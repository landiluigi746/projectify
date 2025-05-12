#include "app/PagesManager.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace projcli
{
    PagesManager::PagesManager() :
        m_Selected(0),
        m_Screen(ftxui::ScreenInteractive::Fullscreen()),
        m_Pages(ftxui::Container::Tab({}, &m_Selected))
    {}

    PagesManager& PagesManager::GetInstance()
    {
        static PagesManager instance;
        return instance;
    }

    void PagesManager::MainLoop()
    {
        m_Screen.Loop(m_Pages);
        m_Screen.Exit();
    }
}
