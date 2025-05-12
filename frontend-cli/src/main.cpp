#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"
#include "api/API.hpp"

#include <print>

using namespace projcli;
using namespace projcli::Pages;

int main()
{
    PagesManager::RegisterPages<
        HomePage,
        SignUpPage,
        SignInPage,
        DashboardPage,
        NewProjectPage,
        ProjectDetailsPage,
        NewTaskPage,
        NewLinkPage
    >();

    std::println("Trying to sign in using stored auth token... ");

    const Result result = API::GetInstance().SignInWithStoredJWT();

    if(result.StatusCode == Status::SUCCESS)
        PagesManager::NavigateTo<DashboardPage>()();
    else
    {
        PagesManager::NavigateTo<HomePage>()();
        std::println("Failed. Redirecting to HomePage");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    PagesManager::GetInstance().MainLoop();

    return 0;
}
