#include "api/API.hpp"

#include <glaze/json/write.hpp>
#include <httplib.h>

namespace projcli
{
    API::API() :
        m_Client("localhost", 8000)
    {}

    API& API::GetInstance()
    {
        static API instance;
        return instance;
    }

    Result API::SignUp(const Credentials& credentials)
    {
        auto res = m_Client.Post("/users/register", glz::write_json(credentials).value(), "application/json");

        if(!res)
            return { Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::Created_201:
                return SignIn(credentials);

            case httplib::StatusCode::BadRequest_400:
                return { Status::FAILURE, "Username or password invalid." };

            case httplib::StatusCode::Conflict_409:
                return { Status::FAILURE, "This username is already registered." };

            default:
                return { Status::FAILURE, "An unknown error occurred." };
        }
    }

    Result API::SignIn(const Credentials& credentials)
    {
        auto res = m_Client.Post("/users/login", glz::write_json(credentials).value(), "application/json");

        if(!res)
            return { Status::FAILURE, httplib::to_string(res.error()) };

        httplib::Headers headers;

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                headers.emplace("Authorization", res.value().get_header_value("Authorization"));
                m_Client.set_default_headers(headers);
                return { Status::SUCCESS, "Successfully registered and logged in!" };

            case httplib::StatusCode::NotFound_404:
                return { Status::FAILURE, "Failed to login!" };

            default:
                return { Status::FAILURE, "An unknown error occurred." };
        }
    }

    Result API::TestSignedIn()
    {
        auto res = m_Client.Get("/protected");

        if(!res)
            return { Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                return { Status::SUCCESS, "Successfully accessed /protected!" };
            case httplib::StatusCode::Unauthorized_401:
                return { Status::FAILURE, "Not authorized." };
            default:
                return { Status::FAILURE, "WTF?" };
        }
    }
}
