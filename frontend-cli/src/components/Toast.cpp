#include "components/Components.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Components
{
    ftxui::Element Toast(std::string_view message, ToastType type)
    {
        ftxui::Color messageColor;

        switch(type)
        {
            case ToastType::INFO:
                messageColor = Color::Default;
                break;
            case ToastType::SUCCESS:
                messageColor = Color::Green;
                break;
            case ToastType::ERROR:
                messageColor = Color::Red;
                break;
        }

        return vbox({
            separatorEmpty(),
            text(std::string(message)) | color(messageColor) | hcenter,
            separatorEmpty()
        });
    }

    ftxui::Component ToastComponent(std::string_view message, ToastType type)
    {
        return Renderer([&] {
            return Components::Toast(message, type);
        });
    }
}
