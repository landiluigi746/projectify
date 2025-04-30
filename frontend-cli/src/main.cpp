#include "app/ComponentManager.hpp"
#include "components/Components.hpp"

using namespace projcli;
using namespace projcli::Components;

int main()
{
    ComponentManager::RegisterComponents<HomePage, SignUpPage, SignInPage>();
    ComponentManager::GetInstance().MainLoop();

    return 0;
}
