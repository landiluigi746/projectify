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
        NewTaskPage
    >();

    const Result result = API::GetInstance().SignInWithStoredJWT();

    if(result.StatusCode == Status::SUCCESS)
        PagesManager::NavigateTo<DashboardPage>()();

    PagesManager::GetInstance().MainLoop();

    return 0;
}
