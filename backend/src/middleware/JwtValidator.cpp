#include "middleware/JwtValidator.hpp"
#include "cfg/Config.hpp"
#include "utils/Utils.hpp"

#include <cctype>
#include <crow.h>
#include <jwt-cpp/jwt.h>

namespace projectify::Middleware
{
    void JwtValidator::before_handle(crow::request& req, crow::response& res, context& ctx)
    {
        const auto [verified, reason] = VerifyToken(req.get_header_value("Authorization"));

        if(!verified)
        {
            res.code = crow::status::UNAUTHORIZED;
            res.end(reason);
        }
    }

    std::pair<bool, std::string> JwtValidator::VerifyToken(const std::string& token)
    {
        try
        {
            const auto decoded = jwt::decode(token);

            if(decoded.has_expires_at())
            {
                const auto now = std::chrono::system_clock::now();

                if(now > decoded.get_expires_at())
                    return std::make_pair(false, "Token expired");
            }
            else
                return std::make_pair(false, "Invalid token");

            if(decoded.has_subject())
            {
                const auto subject = decoded.get_subject();

                if(!Utils::IsPositiveInteger(subject))
                    return std::make_pair(false, "Subject invalid");
            }
            else
                return std::make_pair(false, "Invalid token");

            jwt::verify()
                .with_type("JWS")
                .with_issuer("projectify-auth")
                .allow_algorithm(jwt::algorithm::hs256{Config::JWT_SECRET})
                .verify(decoded);

            return std::make_pair(true, "");
        }
        catch(const std::exception& e)
        {
            return std::make_pair(false, e.what());
        }
    }
}
