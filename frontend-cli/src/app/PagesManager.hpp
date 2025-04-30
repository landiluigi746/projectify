#pragma once

#include <ftxui/component/task.hpp>
#include <iterator>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace projcli
{
    class PagesManager
    {
    public:
        PagesManager(const PagesManager&) = delete;
        PagesManager& operator=(const PagesManager&) = delete;

        static PagesManager& GetInstance();

        template<typename Page>
        static ftxui::Closure NavigateTo()
        {
            return [] {
                GetInstance().NavigateTo_Internal<Page>();
            };
        }

        template<typename... Pages>
        static void RegisterPages()
        {
            GetInstance().Register<Pages...>();
        }

        static ftxui::Closure ExitClosure()
        {
            return GetInstance().m_Screen.ExitLoopClosure();
        }

        void MainLoop();
    private:
        PagesManager();

        template<typename... Pages>
        void Register()
        {
            static_assert((std::is_base_of_v<ftxui::ComponentBase, Pages> && ...), "Pages must derive from ftxui::ComponentBase!");
            (RegisterPage<Pages>(), ...);
        }

        template<typename Page>
        void RegisterPage()
        {
            m_Pages.emplace_back(typeid(Page).name(), ftxui::Make<Page>());
        }

        template<typename Page>
        void NavigateTo_Internal()
        {
            const auto it = std::find_if(std::begin(m_Pages), std::end(m_Pages), [](const auto& mappedPage) {
                return mappedPage.first == typeid(Page).name();
            });

            if(it != m_Pages.end())
                m_Selected = int(std::distance(m_Pages.begin(), it));
        }

        ftxui::Component GetTabContainer();

        int m_Selected;
        ftxui::ScreenInteractive m_Screen;
        std::vector<std::pair<std::string_view, ftxui::Component>> m_Pages;
    };
}
