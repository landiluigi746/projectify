#include "api/API.hpp"
#include "Types.hpp"
#include "utils/Utils.hpp"

#include <cmath>
#include <glaze/core/read.hpp>
#include <glaze/json/write.hpp>
#include <httplib.h>
#include <memory>
#include <utility>

namespace projcli
{
    API::API() :
        m_Client("localhost", 8000)
    {
        m_Client.set_keep_alive(true);
    }

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
        std::string jwt;

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                jwt = res.value().get_header_value("Authorization");

                headers.emplace("Authorization", jwt);
                m_Client.set_default_headers(headers);
                Utils::SaveJWT(jwt);
                return { Status::SUCCESS, "Successfully logged in!" };

            case httplib::StatusCode::NotFound_404:
                return { Status::FAILURE, "Failed to login!" };

            default:
                return { Status::FAILURE, "An unknown error occurred." };
        }
    }

    Result API::SignInWithStoredJWT()
    {
        auto jwt = Utils::LoadJWT();

        if(jwt.empty())
            return { Status::FAILURE, "No JWT found." };

        httplib::Headers headers;
        headers.emplace("Authorization", jwt);

        auto res = m_Client.Post("/users/loginJWT", headers);

        if(!res)
            return { Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                m_Client.set_default_headers(headers);
                return { Status::SUCCESS, "Successfully logged in!" };

            case httplib::StatusCode::Unauthorized_401:
                return { Status::FAILURE, "Not authorized." };

            default:
                return { Status::FAILURE, "WTF?" };
        }
    }

    std::pair<Result, std::vector<Project>> API::GetProjects()
    {
        auto res = m_Client.Post("/projects/get");

        if(!res)
            return std::make_pair(Result{ Status::FAILURE, httplib::to_string(res.error()) }, std::vector<Project>());

        std::vector<Project> projects;

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                if(glz::read_json(projects, res.value().body))
                    return std::make_pair(Result{ Status::FAILURE, "Failed to parse JSON response." }, std::vector<Project>());

                return std::make_pair(Result{ Status::SUCCESS, "Successfully fetched projects!" }, projects);

            case httplib::StatusCode::Unauthorized_401:
                return std::make_pair(Result{ Status::FAILURE, "Not authorized." }, std::vector<Project>());

            default:
                return std::make_pair(Result{ Status::FAILURE, "WTF?" }, std::vector<Project>());
        }
    }
}
