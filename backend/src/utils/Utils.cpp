#include "utils/Utils.hpp"

#include <cstdlib>
#include <string>
#include <string_view>
#include <mutex>
#include <sodium/core.h>
#include <sodium/crypto_pwhash.h>
#include <spdlog/spdlog.h>
#include <jwt-cpp/jwt.h>

namespace projectify::Utils
{
    static std::once_flag s_SodiumInitialized;

    static inline void InitSodium()
    {
        std::call_once(s_SodiumInitialized, [&] {
            if(sodium_init() < 0)
            {
                spdlog::error("Failed to initialize libsodium");
                std::exit(1);
            }
        });
    }

    std::string GetEnv(std::string_view varName, std::string_view defaultValue)
    {
        const char* val = std::getenv(varName.data());
        return (val && val[0] != '\0') ? std::string(val) : std::string(defaultValue);
    }

    std::string HashString(std::string_view string)
    {
        InitSodium();

        char hashed[crypto_pwhash_STRBYTES];

        if(crypto_pwhash_str(hashed, string.data(), string.length(), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
        {
            spdlog::error("Failed to hash string");
            return std::string("");
        }

        return std::string(hashed);
    }

    bool CheckHashedString(std::string_view string, std::string_view hashed)
    {
        InitSodium();
        return (crypto_pwhash_str_verify(hashed.data(), string.data(), string.length()) == 0);
    }

    bool RegexMatches(std::string_view str, const std::regex& regex)
    {
        return std::regex_match(str.begin(), str.end(), regex);
    }

    std::string CreateJwt(int id)
    {
        return jwt::create()
            .set_type("JWS")
            .set_issuer("projectify-auth")
            .set_issued_now()
            .set_expires_in(std::chrono::seconds{3600})
            .set_subject(std::to_string(id))
            .sign(jwt::algorithm::hs256{Config::JWT_SECRET});
    }

    bool IsPositiveInteger(std::string_view str)
    {
        return (!str.empty() && std::all_of(str.begin(), str.end(), [](char c) {
            return std::isdigit(c);
        }));
    }
}
