#include "components/Components.hpp"

#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Components::Utils
{
    Element Banner()
    {
        return vbox({
            text(R"(                     _              _    _   __        )"),
            text(R"(                    (_)            | |  (_) / _|       )"),
            text(R"(  _ __   _ __  ___   _   ___   ___ | |_  _ | |_  _   _ )"),
            text(R"( | '_ \ | '__|/ _ \ | | / _ \ / __|| __|| ||  _|| | | |)"),
            text(R"( | |_) || |  | (_) || ||  __/| (__ | |_ | || |  | |_| |)"),
            text(R"( | .__/ |_|   \___/ | | \___| \___| \__||_||_|   \__, |)"),
            text(R"( | |               _/ |                           __/ |)"),
            text(R"( |_|              |__/                           |___/ )")
        }) | hcenter | bold;
    }
}
