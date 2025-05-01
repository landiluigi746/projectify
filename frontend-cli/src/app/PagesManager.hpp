#pragma once

#include <ftxui/component/task.hpp>
#include <iterator>
#include <memory>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace projcli
{
    template<typename T, typename = void>
    struct HasOnEnter : std::false_type {};

    template<typename T>
    struct HasOnEnter<T, std::void_t<decltype(&T::OnEnter)>> : std::true_type {};

    template<typename T>
    constexpr bool HasOnEnter_v = HasOnEnter<T>::value;

    class PagesManager
    {
    public:
        PagesManager(const PagesManager&) = delete;
        PagesManager& operator=(const PagesManager&) = delete;

        static PagesManager& GetInstance();

        template<typename Page>
        static ftxui::Closure NavigateTo()
        {
            static_assert((std::is_base_of_v<ftxui::ComponentBase, Page>), "Page must derive from ftxui::ComponentBase!");

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
            m_PagesIDs.emplace_back(typeid(Page).name());
            m_Pages->Add(ftxui::Make<Page>());
        }

        template<typename Page, typename... Args>
        void NavigateTo_Internal(Args&&... args)
        {
            const auto it = std::find_if(std::begin(m_PagesIDs), std::end(m_PagesIDs), [](std::string_view id) {
                return id == typeid(Page).name();
            });

            if(it != m_PagesIDs.end())
            {
                m_Selected = int(std::distance(m_PagesIDs.begin(), it));

                if constexpr(HasOnEnter_v<Page>)
                    std::dynamic_pointer_cast<Page>(m_Pages->ChildAt(m_Selected))->OnEnter(std::forward<Args>(args)...);
            }
        }

        int m_Selected;
        ftxui::ScreenInteractive m_Screen;
        std::vector<std::string_view> m_PagesIDs;
        ftxui::Component m_Pages;
    };
}
