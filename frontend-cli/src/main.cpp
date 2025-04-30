#include "app/PagesManager.hpp"
#include "pages/Pages.hpp"

using namespace projcli;
using namespace projcli::Pages;

int main()
{
    PagesManager::RegisterPages<HomePage, SignUpPage, SignInPage, DashboardPage>();
    PagesManager::GetInstance().MainLoop();

    return 0;
}
