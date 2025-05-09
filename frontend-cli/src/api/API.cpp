#include "api/API.hpp"
#include "Types.hpp"
#include "utils/Utils.hpp"

#include <cmath>
#include <glaze/glaze.hpp>
#include <glaze/json/json_t.hpp>
#include <httplib.h>
#include <utility>

namespace projcli
{
    API::API() :
        m_Client(Utils::GetEnv("PROJECTIFY_BACKEND_URL", "https://projectify-y4so.onrender.com"))
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

            default:
                return { Status::FAILURE, res.value().body };
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

            default:
                return { Status::FAILURE, res.value().body };
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

            default:
                return { Status::FAILURE, res.value().body };
        }
    }

    void API::SignOut()
    {
        m_Client.set_default_headers({});
        Utils::ClearJWT();
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

            default:
                return std::make_pair(Result{ Status::FAILURE, res.value().body }, std::vector<Project>());
        }
    }

    Result API::CreateProject(std::string_view name, std::string_view description)
    {
        glz::json_t json = {{"name", name}, {"description", description}};
        auto res = m_Client.Post("/projects/register", glz::write_json(json).value(), "application/json");

        if(!res)
            return Result{ Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::Created_201:
                return Result{ Status::SUCCESS, "Successfully created project!" };

            default:
                return Result{ Status::FAILURE, res.value().body };
        }
    }

    Result API::DeleteProject(int projectID)
    {
        glz::json_t json = {{"projectID", projectID}};
        auto res = m_Client.Post("/projects/delete", glz::write_json(json).value(), "application/json");

        if(!res)
            return Result{ Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                return Result{ Status::SUCCESS, "Successfully deleted project!" };

            default:
                return Result{ Status::FAILURE, res.value().body };
        }
    }

    std::pair<Result, std::vector<Task>> API::GetTasks(int projectID)
    {
        glz::json_t json = {{"projectID", projectID}};
        auto res = m_Client.Post("/tasks/get", glz::write_json(json).value(), "application/json");

        if(!res)
            return std::make_pair(Result{ Status::FAILURE, httplib::to_string(res.error()) }, std::vector<Task>());

        std::vector<Task> tasks;

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                if(glz::read_json(tasks, res.value().body))
                    return std::make_pair(Result{ Status::FAILURE, "Failed to parse JSON response." }, std::vector<Task>());

                return std::make_pair(Result{ Status::SUCCESS, "Successfully fetched tasks!" }, tasks);

            default:
                return std::make_pair(Result{ Status::FAILURE, res.value().body }, std::vector<Task>());
        }
    }

    Result API::CreateTask(int projectID, std::string_view name)
    {
        glz::json_t json = {{"projectID", projectID}, {"name", name}};
        auto res = m_Client.Post("/tasks/register", glz::write_json(json).value(), "application/json");

        if(!res)
            return Result{ Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::Created_201:
                return Result{ Status::SUCCESS, "Successfully created task!" };

            default:
                return Result{ Status::FAILURE, res.value().body };
        }
    }

    Result API::ToggleTaskStatus(int projectID, int taskID)
    {
        glz::json_t json = {{"projectID", projectID}, {"taskID", taskID}};
        auto res = m_Client.Post("/tasks/toggleStatus", glz::write_json(json).value(), "application/json");

        if(!res)
            return Result{ Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                return Result{ Status::SUCCESS, "Successfully toggled task status!" };

            default:
                return Result{ Status::FAILURE, res.value().body };
        }
    }

    Result API::DeleteTask(int projectID, int taskID)
    {
        glz::json_t json = {{"projectID", projectID}, {"taskID", taskID}};
        auto res = m_Client.Post("/tasks/delete", glz::write_json(json).value(), "application/json");

        if(!res)
            return Result{ Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                return Result{ Status::SUCCESS, "Successfully deleted task!" };

            default:
                return Result{ Status::FAILURE, res.value().body };
        }
    }

    std::pair<Result, std::vector<Link>> API::GetLinks(int projectID)
    {
        glz::json_t json = {{"projectID", projectID}};
        auto res = m_Client.Post("/links/get", glz::write_json(json).value(), "application/json");

        if(!res)
            return std::make_pair(Result{ Status::FAILURE, httplib::to_string(res.error()) }, std::vector<Link>());

        std::vector<Link> links;

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                if(glz::read_json(links, res.value().body))
                    return std::make_pair(Result{ Status::FAILURE, "Failed to parse JSON response." }, std::vector<Link>());

                return std::make_pair(Result{ Status::SUCCESS, "Successfully fetched links!" }, links);

            default:
                return std::make_pair(Result{ Status::FAILURE, res.value().body }, std::vector<Link>());
        }
    }

    Result API::CreateLink(int projectID, std::string_view name, std::string_view url)
    {
        glz::json_t json = {{"projectID", projectID}, {"name", name}, {"url", url}};
        auto res = m_Client.Post("/links/register", glz::write_json(json).value(), "application/json");

        if(!res)
            return Result{ Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::Created_201:
                return Result{ Status::SUCCESS, "Successfully created link!" };

            default:
                return Result{ Status::FAILURE, res.value().body };
        }
    }

    Result API::DeleteLink(int projectID, int linkID)
    {
        glz::json_t json = {{"projectID", projectID}, {"linkID", linkID}};
        auto res = m_Client.Post("/links/delete", glz::write_json(json).value(), "application/json");

        if(!res)
            return Result{ Status::FAILURE, httplib::to_string(res.error()) };

        switch(res.value().status)
        {
            case httplib::StatusCode::OK_200:
                return Result{ Status::SUCCESS, "Successfully deleted link!" };

            default:
                return Result{ Status::FAILURE, res.value().body };
        }
    }
}
