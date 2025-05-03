#include "components/Components.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Components
{
    ftxui::Element Toast(std::string_view message, Status type)
    {
        if(message.empty())
            return emptyElement();

        ftxui::Color messageColor;

        switch(type)
        {
            case Status::INFO:
                messageColor = Color::Default;
                break;
            case Status::SUCCESS:
                messageColor = Color::Green;
                break;
            case Status::FAILURE:
                messageColor = Color::Red;
                break;
        }

        return vbox({
            separatorEmpty(),
            text(std::string(message)) | color(messageColor) | hcenter,
            separatorEmpty()
        });
    }

    ftxui::Component ToastComponent(std::string_view message, Status type)
    {
        return Renderer([=] {
            return Components::Toast(message, type);
        });
    }
}
