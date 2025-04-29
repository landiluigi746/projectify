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
    class ComponentManager
    {
    public:
        ComponentManager(const ComponentManager&) = delete;
        ComponentManager& operator=(const ComponentManager&) = delete;

        static ComponentManager& GetInstance();

        template<typename Component>
        static ftxui::Closure NavigateTo()
        {
            return [] {
                GetInstance().NavigateTo_Internal<Component>();
            };
        }

        template<typename... Components>
        static void RegisterComponents()
        {
            GetInstance().Register<Components...>();
        }

        ftxui::Component GetTabContainer();
    private:
        ComponentManager();

        template<typename... Components>
        void Register()
        {
            static_assert((std::is_base_of_v<ftxui::ComponentBase, Components> && ...), "Components must derive from ftxui::ComponentBase!");
            (RegisterComponent<Components>(), ...);
        }

        template<typename Component>
        void RegisterComponent()
        {
            m_Components.emplace_back(typeid(Component).name(), ftxui::Make<Component>());
        }

        template<typename Component>
        void NavigateTo_Internal()
        {
            const auto it = std::find_if(std::begin(m_Components), std::end(m_Components), [](const auto& mappedComponent) {
                return mappedComponent.first == typeid(Component).name();
            });

            if(it != m_Components.end())
                m_Selected = int(std::distance(m_Components.begin(), it));
        }

        int m_Selected;
        std::vector<std::pair<std::string_view, ftxui::Component>> m_Components;
    };
}
