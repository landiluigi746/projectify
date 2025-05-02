#pragma once

#include "Types.hpp"
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

namespace projcli::Components
{
    ftxui::Element Banner();
    ftxui::Component ProjectCard(const Project& project);
    ftxui::Component ProjectList(const std::vector<Project>& projects);

    enum class ToastType
    {
        INFO,
        SUCCESS,
        ERROR
    };

    ftxui::Element Toast(std::string_view message, ToastType type);
    ftxui::Component ToastComponent(std::string_view message, ToastType type);
}
