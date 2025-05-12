#include "Types.hpp"
#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "components/Components.hpp"
#include "api/API.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

namespace projcli::Pages
{
    NewLinkPage::NewLinkPage()
    {
        m_LinkNameInput = Input(&m_LinkName, "Link name", InputOption{ .multiline = false });
        m_LinkURLInput = Input(&m_LinkURL, "Link URL", InputOption{ .multiline = false });

        m_CreateButton = Button("Create", [&] {
            DoCreateLink();
        }, ButtonOption::Animated());

        m_BackButton = Button("Back", PagesManager::NavigateTo<ProjectDetailsPage>(m_Project), ButtonOption::Animated());

        Add(Container::Vertical({
            m_LinkNameInput,
            m_LinkURLInput,
            m_CreateButton,
            m_BackButton
        }));
    }

    Element NewLinkPage::OnRender()
    {
        return vbox({
            Components::Banner(),
            separatorEmpty(),
            window(
                text(std::format("New link on project: {}", m_Project.name)) | hcenter | bold,
                vbox({
                    paragraph("Name must be between 6 and 64 characters and must start with a letter") | color(Color::Yellow),

                    separatorEmpty(),

                    m_LinkNameInput->Render() | borderRounded,
                    m_LinkURLInput->Render() | borderRounded,

                    Components::Toast(m_Result.Message, m_Result.StatusCode),

                    hbox({
                        m_CreateButton->Render(),
                        separatorEmpty(),
                        m_BackButton->Render()
                    }) | hcenter
                })
            ) | size(WIDTH, EQUAL, 70)
        }) | center | yflex;
    }

    void NewLinkPage::DoCreateLink()
    {
        m_Result = API::GetInstance().CreateLink(m_Project.ID, m_LinkName, m_LinkURL);

        if(m_Result.StatusCode == Status::FAILURE)
            return;

        PagesManager::NavigateTo<ProjectDetailsPage>(m_Project)();
    }

    void NewLinkPage::OnEnter(const Project& project)
    {
        m_Project = project;
        m_LinkName.clear();
        m_LinkURL.clear();
    }
}
