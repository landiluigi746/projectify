#include "Types.hpp"
#include "api/API.hpp"

#include <print>

int main()
{
    using namespace projcli;

    API::API api;

    Credentials credentials = {
        "mycoolusername1",
        "Bingojingo_1"
    };

    auto res = api.TestSignedIn();
    std::println("Status: {} | Message: {}", API::StatusToString(res.StatusCode), res.Message);

    res = api.SignUp(credentials);
    std::println("Status: {} | Message: {}", API::StatusToString(res.StatusCode), res.Message);

    res = api.TestSignedIn();
    std::println("Status: {} | Message: {}", API::StatusToString(res.StatusCode), res.Message);

    return 0;
}
