#pragma once

#include "Types.hpp"
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

namespace projcli::Components
{
    ftxui::Element Banner();
    ftxui::Component ProjectCard(const Project& project);
    ftxui::Component ProjectList(const std::vector<Project>& projects);

    ftxui::Component TaskCard(const Task& task);
    ftxui::Component TaskList(const std::vector<Task>& tasks);

    ftxui::Element Toast(std::string_view message, Status status);
    ftxui::Component ToastComponent(std::string_view message, Status status);
}
