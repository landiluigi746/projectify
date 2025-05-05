#pragma once

#include "Types.hpp"
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>

namespace projcli::Components
{
    ftxui::Element Banner();
    ftxui::Component ProjectCard(const Project& project);
    ftxui::Component ProjectList(const std::vector<Project>& projects);

    ftxui::Component TaskCard(const Task& task, Result& resultRef);
    ftxui::Component TaskList(const std::vector<Task>& tasks, Result& resultRef);

    ftxui::Component LinkCard(const Link& link);
    ftxui::Component LinkList(const std::vector<Link>& link);

    ftxui::Element Toast(std::string_view message, Status status);
    ftxui::Component ToastComponent(std::string_view message, Status status);
}
